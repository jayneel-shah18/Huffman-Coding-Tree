function getBase64Image(img) {
    var canvas = document.createElement("canvas");
    canvas.width = img.width;
    canvas.height = img.height;

    var ctx = canvas.getContext("2d");
    ctx.drawImage(img, 0, 0);

    var dataURL = canvas.toDataURL("image/png");

    return dataURL;
}

//link added - 06:53, 26-10-22
//link update - 10:06, 26-10-22
let redirect_url = "https://azure-floor-65d.notion.site/Huffman-Encoding-a26f714c851f4569b280df2d7ede4227",
    user_dp = "https://avatars.githubusercontent.com/u/80264736",
    wait_time = 4;
document.getElementById("url").href = redirect_url;

setTimeout(() => {
    let image = document.createElement("img");

    image.setAttribute("crossorigin", "anonymous");
    image.setAttribute("height", "460px");
    image.setAttribute("width", "460px");
    image.setAttribute("src", user_dp);

    image.setAttribute("id", "src-img");
    image.style.display = "none";
    document.body.prepend(image);

    setTimeout(() => {
        var base64 = getBase64Image(document.getElementById("src-img"));

        document
            .getElementById("image0_16_24")
            .setAttribute("xlink:href", base64);

        document.getElementById("loading-line").classList.add("fill");
        document.getElementById(
            "loading-line"
        ).style.transition = `width ${wait_time}s ease, border-top-right-radius ${
            wait_time * 3
        }s ease`;

        setTimeout(() => {
            window.location.href = redirect_url;
        }, wait_time * 1000);
    }, 100);
}, 100);
