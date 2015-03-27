(function() {
    var request = new XMLHttpRequest();
    request.open("GET", "http://127.0.0.1:8080/gem/1/show.json");
    request.send();
    request.onload = function(e) {
        const dailies = JSON.parse(request.responseText);
        displayDailies(dailies); 
    }

    function displayDailies(dailies) {
        const table = document.getElementById("dailies");
        var body = table.getElementsByTagName("tbody")[0];
        dailies.forEach(function (daily) {
            var dailyRow = document.createElement("tr");
            body.appendChild(dailyRow);

            var downloadsElement = document.createElement("td");
            body.appendChild(downloadsElement);
            downloadsElement.innerHTML = daily.downloads;

            var dateElement = document.createElement("td");
            body.appendChild(dateElement);
            dateElement.innerHTML = daily.date;
        });

        console.log(getQueryParams());
    }

    function getQueryParams() {
        const rawParams = window.location.search.substring(1);
        var params = {};

        // Exit early if posible
        if (rawParams.length === 0) {
            return params;
        }

        var moreParamsExist = true;
        var startPosition = 0;
        while (moreParamsExist) {
            var nextAmpersand = rawParams.indexOf("&", startPosition);
            
            if (nextAmpersand === -1) {
                nextAmpersand = rawParams.length;
                moreParamsExist = false;
            }
        
            const rawParam = rawParams.substring(startPosition, nextAmpersand);
            const result = rawParam.split("=");
            params[result[0]] = result[1];
            
            startPosition = nextAmpersand + 1;
        }

        return params;
    }
})();

