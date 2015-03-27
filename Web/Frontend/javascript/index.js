(function() {
    var request = new XMLHttpRequest();
    request.open("GET", "http://127.0.0.1:8080/gems/index.json");
    request.send();
    request.onload = function(e) {
        const gems = JSON.parse(request.responseText);
        displayGems(gems); 
    }

    function displayGems(gems) {
        var listDiv = document.getElementById("gems-list");
        gems.forEach(function (gem) {
            const divStructure = listDiv.getElementsByClassName("gem")[0];
            var gemDiv = divStructure.cloneNode(true);
            listDiv.appendChild(gemDiv);

            var nameLink = gemDiv.getElementsByClassName("name")[0];
            nameLink.innerHTML = gem.name;
            nameLink.setAttribute("href", "gem.html?id=" + gem.id);
        });
    }
})();

