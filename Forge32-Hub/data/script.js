function sendButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/connect_click", true); // Send a GET request to /connect_click
    xhr.send();
}

function disconnectButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/disconnect_click", true); // Send a GET request to /disconnect_click
    xhr.send();
}