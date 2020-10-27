function submit_form() {
    let checkbox = document.getElementById("privacy_check").checked;
    if (checkbox === true) {
        console.log("submitting");
        window.open('/success.html', '_self');
    }
    else {
        let info = document.getElementById("info");
        info.innerHTML = "Please accept privacy terms."
        info.style.display = "block";
        console.log("please accept privacy")
    }
     
}
