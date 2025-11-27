/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatedTest.js                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:15:52 by capapes           #+#    #+#             */
/*   Updated: 2025/11/27 18:40:43 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



const net = require("net");

const ports = [8080, 8081, 8082];
const host = "127.0.0.1";

// --- CONFIG ---
const CONNECTION_TIMEOUT = 2000; // ms
const RESPONSE_TIMEOUT = 2000;   // ms
// ---------------

// Valid HTTP request
const GOOD_REQUEST =
    "GET /localhost/ HTTP/1.1\r\n" +
    "Host: hola.com\r\n" +
    "Connection: close\r\n" +
    "\r\n";

// // Invalid HTTP request (malformed)
// const BAD_REQUEST =
//     "GARBAGE /??\r\n" +
//     "BadHeader no-colon\r\n" +
//     "\r\n";

function connect(port) {
    return new Promise(resolve => {
        const socket = net.createConnection({ host, port });

        let done = false;
        const start = Date.now();

        socket.setTimeout(CONNECTION_TIMEOUT);

        socket.on("connect", () => {
            const ms = Date.now() - start;
            console.log(`✓ Connected to ${host}:${port} in ${ms}ms`);
            done = true;
            resolve({ socket, ok: true });
        });

        socket.on("timeout", () => {
            if (!done) {
                console.log(`✗ Connection timeout on ${host}:${port}`);
                socket.destroy();
                resolve({ ok: false });
            }
        });

        socket.on("error", err => {
            if (!done) {
                console.log(`✗ Failed to connect to ${host}:${port} (${err.code})`);
                resolve({ ok: false });
            }
        });
    });
}
function sendRequest(socket, port, label, request) {
    return new Promise(resolve => {
        let response = "";
        let ended = false;

        // socket.setTimeout(RESPONSE_TIMEOUT);

        socket.on("data", chunk => {
            response += chunk.toString();
        });

        socket.on("end", () => {
            ended = true;
            resolve({ ok: true, response });
        });

        socket.on("timeout", () => {
            if (!ended) {
                socket.destroy();
                resolve({ ok: false, response: "(timeout)" });
            }
        });

        socket.on("error", err => {
            resolve({ ok: false, response: `(error: ${err.message})` });
        });

        socket.write(request);
    });
}



async function testPort(port) {
    console.log(`\n=== Testing port ${port} ===`);

    const conn = await connect(port);
    if (!conn.ok) return { port, ok: false };

    const socket = conn.socket;

    // GOOD REQUEST
    const good = await sendRequest(socket, port, "GOOD REQUEST", GOOD_REQUEST);
    console.log(`--- GOOD RESPONSE (${port}) ---`);
    console.log(good.response.trim() || "(empty)");
    console.log("------------------------------\n");

    socket.end();

    // BAD REQUEST
    // const conn2 = await connect(port);
    // if (!conn2.ok) return { port, ok: false };

    // const socket2 = conn2.socket;

    // const bad = await sendRequest(socket2, port, "BAD REQUEST", BAD_REQUEST);
    // console.log(`--- BAD RESPONSE (${port}) ---`);
    // console.log(bad.response.trim() || "(empty)");
    // console.log("------------------------------\n");

    // socket2.end();

    return { port, ok: good.ok && bad.ok };
}
(async () => {
    console.log("Running enhanced port tests...\n");

    const results = await Promise.all(ports.map(testPort));

    console.log("=== Summary ===");
    results.forEach(r => {
        console.log(` - ${r.port}: ${r.ok ? "OK" : "FAIL"}`);
    });

    const failed = results.filter(r => !r.ok).length;
    process.exit(failed ? 1 : 0);
})();
