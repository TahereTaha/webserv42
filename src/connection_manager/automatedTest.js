/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatedTest.js                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:15:52 by capapes           #+#    #+#             */
/*   Updated: 2025/12/01 18:56:54 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const net = require("net");

const ports = [8080];
const host = "127.0.0.1";

const CONNECTION_TIMEOUT = 2000; // ms
const RESPONSE_TIMEOUT = 2000; // ms

const testCases = [
  // {
  //   label: "GOOD REQUEST",
  //   request:
  //     "GET / HTTP/1.1\r\n" +
  //     "Host: hola.com\r\n" +
  //     "Connection: close\r\n" +
  //     "\r\n",
  //   expectedStatus: 200,
  // },
  {
    label: "BAD REQUEST",
    request: "GARBAGE /??\r\n" + "BadHeader no-colon\r\n" + "\r\n",
    expectedStatus: 400,
  },
];

const fullTestCases = testCases.flatMap((test) => {
  return ports.map((port) => ({ port, test }));
});

function connect(port) {
  return new Promise((resolve) => {
    const socket = net.createConnection({ host, port });
    let done = false;
    const start = Date.now();

    socket.setTimeout(CONNECTION_TIMEOUT);

    socket.on("connect", () => {
      const ms = Date.now() - start;
      done = true;
      resolve({ socket, ok: true, response: `Connected in ${ms}ms` });
    });

    socket.on("timeout", () => {
      if (!done) {
        socket.destroy();
        resolve({ ok: false, response: "(timeout)" });
      }
    });

    socket.on("error", (err) => {
      if (!done) {
        resolve({ ok: false, response: `(error: ${err.message})` });
      }
    });
  });
}

function sendRequest(socket, request) {
  return new Promise((resolve) => {
    let response = "";
    let ended = false;

    socket.setTimeout(RESPONSE_TIMEOUT);

    socket.on("data", (chunk) => {
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

    socket.on("error", (err) => {
      resolve({ ok: false, response: `(error: ${err.message})` });
    });

    socket.write(request);
  });
}

async function testPort(port, test) {
  const conn = await connect(port);
  const response = `${port} ${test.label}\n${conn.response}`;
  if (!conn.ok)
    return {
      response,
      ok: false,
      testResult: false,
    };
  const socket = conn.socket;
  const res = await sendRequest(socket, test.request);
  socket.end();
  return {
    response: `${response}\n${res.response}`,
    ok: res.ok,
    testResult: res.response.includes(`HTTP/1.1 ${test.expectedStatus}`),
  };
}

(async () => {
  console.log("Running enhanced port tests...\n");

  const results = await Promise.all(
    fullTestCases.map(({ port, test }) => testPort(port, test))
  );

  results.forEach((r) => {
    console.log(`${r.testResult ? "PASS" : "FAIL"}: ${r.response} \n`);
  });

  const failed = results.filter((r) => !r.ok).length;
  process.exit(failed ? 1 : 0);
})();
