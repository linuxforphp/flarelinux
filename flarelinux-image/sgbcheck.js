'use strict';

const http = require('http');

let url = "http://localhost:9650/ext/health";

http.get(url,(res) => {
    let body = "";

    res.on("data", (chunk) => {
        body += chunk;
    });

    res.on("end", () => {
        try {
            let json = JSON.parse(body);
            
            if (json.checks.network.message.connectedPeers && json.checks.network.message.connectedPeers > 5) {
                console.log(0);
            } else {
                console.log(1);
            }
        } catch (error) {
            console.log(1);
        };
    });

}).on("error", (error) => {
    console.log(1);
});
