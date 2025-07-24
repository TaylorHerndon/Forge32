function appendHtmlIntoDiv(divId, htmlFilePath) {
    fetch(htmlFilePath)
        .then(response => response.text())
        .then(data => {
            document.getElementById(divId).insertAdjacentHTML('beforeend', data);
        })
        .catch(error => {
            console.error('Error loading HTML:', error);
        });
}

function updateDynamicContent() {
    fetch("/dynamic-content")
        .then(response => response.text())
        .then(data => {
            objects = data.split(",");
            if (objects.length === 0 || (objects.length === 1 && objects[0] === "")) { return; }
            document.getElementById("dynamic-content").innerHTML = "";
            objects.forEach(function (object) {
                var sect = document.createElement("section");
                sect.className = "white-border";
                sect.innerHTML = "<h2>Object</h2>";
                button = document.createElement("button");
                button.innerHTML = object;
                button.className = "button-blue";
                sect.appendChild(button);
                document.getElementById("dynamic-content").appendChild(sect);
            });
        })
        .catch(error => {
            console.error('Error fetching dynamic content:', error);
        });
}

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
        }
    };
    currentTimeRequest.open("GET", "/servertime", true);
    currentTimeRequest.send();
}