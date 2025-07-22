function connectButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/connect_click", true); // Send a GET request to /connect_click
    xhr.send();
}

function disconnectButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/disconnect_click", true); // Send a GET request to /disconnect_click
    xhr.send();
}

function updateCurrentTime() {
    var currentTimeRequest = new XMLHttpRequest();
    currentTimeRequest.onreadystatechange = function () {
        if (currentTimeRequest.readyState === 4 && currentTimeRequest.status === 200) {
            document.getElementById('current-time').innerHTML = currentTimeRequest.responseText;
            // Apparently we can do this with jQuery, but something is wrong with the jQuery library
            // $('#current-time').html(currentTimeRequest.responseText);
        }
    };
    currentTimeRequest.open("GET", "/servertime", true);
    currentTimeRequest.send();
}