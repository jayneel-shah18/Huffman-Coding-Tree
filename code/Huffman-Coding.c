// 20BCE090, 20BCE100, 20BCE105
// Het Patel, Jainik Bakshi, Jayneel Shah
// Digital Communications Assignment
// Huffman Coding

// example: mississippi
//  m-1 i-4 s-4
//  the heap tree which would be created to get the huffman codes
//
//                     11
//                   0/  \1 
//                   s    7 
//                      0/ \1
//                      3   i
//                    0/ \1
//                    m   p 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 150

struct node
{
        char ch;
        int freq;
        struct node* left;
        struct node* right;
};

struct node* heap[SIZE];

int heapSize = 0;

void insertHeapArray(struct node *element)
{
        // incrementing the heap size by 1 and assigning the node to last index
        heapSize++;
        heap[heapSize] = element;

        int current = heapSize;

        // swapping the child and parent if the frequency of parent is more than the frequency of child
        while (heap[current / 2]->freq > element->freq)
        {
                heap[current] = heap[current / 2];
                current /= 2;
        }
        heap[current] = element;
}

// function returns minimum frequancy of the element and rearranges the heap in needed manner
struct node* DeleteMin()
{
        // node to store the last and min element which we will need to swap in the end
        struct node *minElement, *lastElement;

        int current;
        int child;

        minElement = heap[1];
        lastElement = heap[heapSize--];
        for (current = 1; current*2 <= heapSize; current = child)
        {
                child = current*2;
                if (child != heapSize && heap[child + 1]->freq < heap[child]->freq)
                {
                        child++;
                }
                if (lastElement->freq > heap[child]->freq)
                {
                        heap[current] = heap[child];
                }
                else
                {
                        break;
                }
        }
        heap[current] = lastElement;
        return minElement;
}

void printTable(struct node* tree, char* code)
{
        if (tree->left == NULL && tree->right == NULL)
        {
                printf("\t\t\t|\t%c\t|\t%s\t\t|\n", tree->ch, code);
                return;
        }

        char leftcode[10], rightcode[10];
        strcpy(leftcode, code);
        strcpy(rightcode, code);

        // as we move left, on our way to leaf node we append 0 to the code word
        leftcode[strlen(code)] = '0';
        leftcode[strlen(code) + 1] = '\0';

        // as we move right, our way to leaf node we append 1 to the code word
        rightcode[strlen(code)] = '1';
        rightcode[strlen(code) + 1] = '\0';
  
        printTable(tree->left, leftcode);
        printTable(tree->right, rightcode);
}

int main()
{

        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\tHuffman Coding\n");
        printf("\n---------------------------------------------------------------------------------------------\n");

        heap[0] = (struct node *)malloc(sizeof(struct node));
        heap[0]->freq = 0;

        char string[500];
        int total = 0;
        printf("\n\n\t\t\tEnter the input data stream:");
        fflush(stdin);

        scanf("%[^\n]%*c", string);

        int noOfChar = 0;

        // constructing the frequency table
        int initialFreq[257] = {0};
        for (int i = 0; i < strlen(string); i++)
        {
                for (int j = 0; j < 257; j++)
                {
                        if (string[i] == j)
                        {
                                initialFreq[j]++;
                        }
                }
        }
        // the frequencies with 0 are not included and we calculate the total number of characters
        for (int i = 0; i < 257; i++)
        {
                if (initialFreq[i] != 0)
                {
                        noOfChar++;
                }
        }
        
        // making an array for storing the freq an the characters present in the stirng entered
        char ch[noOfChar];
        int freq[noOfChar];
        int i = 0;
        for (int j = 0; j < 257; j++)
        {
                if (initialFreq[j] != 0)
                {
                        freq[i] = initialFreq[j];
                        ch[i] = j;
                        i++;
                }
        }

        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\tThe Frequency Table\n");
        printf("\n---------------------------------------------------------------------------------------------\n\n");

        printf("\t\t\t|\tChar\t|\tFreq\t|\n");        
        for (int k = 0; k < noOfChar; k++)
        {
                printf("\t\t\t|\t%c\t|\t%d\t|\n", ch[k], freq[k]);
                total += freq[k];
        }
        printf("\t\t\t\tTotal:\t\t%d\n",total);
    
        // creating the heap tree 
        for (int l = 0; l < noOfChar; l++)
        {
                struct node* temp = (struct node*)malloc(sizeof(struct node));
                temp->ch = ch[l];
                temp->freq = freq[l];
                temp->left = temp->right = NULL;
                insertHeapArray(temp);
        }
  
        printf("\n---------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\tThe Huffman Code Table\n");
        printf("\n---------------------------------------------------------------------------------------------\n\n");
        printf("\t\t\t|\tChar\t|\tCode\t\t|\n");
        if (noOfChar == 1)
        {
                printf("\t\t\t|\t\t%c\t|\t0\t\t|\n", ch);
        }
        
        // creating the tree with the total as the sum of frequency of left and right child
        for (i = 0; i < noOfChar - 1; i++)
        {
                struct node* leftptr = DeleteMin();
                struct node* rightptr = DeleteMin();
                struct node* temp = (struct node*)malloc(sizeof(struct node));
                temp->ch = '\0';
                temp->left = leftptr;
                temp->right = rightptr;
                temp->freq = leftptr->freq + rightptr->freq;
                // inserting the entire node into the heap array
                insertHeapArray(temp);
        }

        struct node *tree = DeleteMin();

        char code[10];
        code[0] = '\0';
        printTable(tree, code);
        printf("\n\n");
}
