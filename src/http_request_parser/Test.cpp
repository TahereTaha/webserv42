/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:51:48 by capapes           #+#    #+#             */
/*   Updated: 2025/07/30 18:20:54 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Test.hpp"

// =====================================================================
// 	TESTS
// =====================================================================
typedef std::vector<TestCase> testCases;

testCases getTestCases() {
    testCases cases;

    // =========================
    // VALID CASES
    // =========================

    // Case 1: Basic GET
    {
        Headers hdrs;
        hdrs["Host"] = "example.com";
        hdrs["User-Agent"] = "TestAgent";
        Request req(ControlData("GET", "/index.html", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "GET /index.html HTTP/1.1\r\nHost: example.com\r\nUser-Agent: TestAgent\r\n\r\n",
            req
        ));
    }

    // Case 2: POST with JSON body
    {
        Headers hdrs;
        hdrs["Content-Type"] = "application/json";
        hdrs["Content-Length"] = "34";
        Request req(ControlData("POST", "/submit", "HTTP/1.1"), hdrs, "{\"key\":\"value\"}");
        cases.push_back(TestCase(
            "POST /submit HTTP/1.1\r\nContent-Type: application/json\r\nContent-Length: 34\r\n\r\n{\"key\":\"value\"}",
            req
        ));
    }

    // Case 3: PUT with Authorization
    {
        Headers hdrs;
        hdrs["Authorization"] = "Bearer token123";
        Request req(ControlData("PUT", "/update", "HTTP/2.0"), hdrs, "");
        cases.push_back(TestCase(
            "PUT /update HTTP/2.0\r\nAuthorization: Bearer token123\r\n\r\n",
            req
        ));
    }

    // Case 4: HEAD request (no body, still valid)
    {
        Headers hdrs;
        hdrs["Host"] = "example.com";
        Request req(ControlData("HEAD", "/check", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "HEAD /check HTTP/1.1\r\nHost: example.com\r\n\r\n",
            req
        ));
    }

    // Case 5: GET with query parameters
    {
        Headers hdrs;
        hdrs["Host"] = "example.com";
        Request req(ControlData("GET", "/search?q=test&lang=en", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "GET /search?q=test&lang=en HTTP/1.1\r\nHost: example.com\r\n\r\n",
            req
        ));
    }

    // =========================
    // INVALID CASES
    // =========================

    // Case 6: Missing HTTP version
    {
        Headers hdrs; // No headers due to malformed request
        Request req(ControlData("GET", "/index.html", ""), hdrs, "");
        req.setErrorCode(400); // Expected: invalid, parser may reject
        cases.push_back(TestCase(
            "GET /index.html\r\nHost: example.com\r\n\r\n",
            req // Expected: invalid, parser may reject
        ));
    }

    // Case 7: Missing Host header in HTTP/1.1
    {
        Headers hdrs;
        Request req(ControlData("GET", "/index.html", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "GET /index.html HTTP/1.1\r\n\r\n",
            req // Expected: invalid (Host required by HTTP/1.1)
        ));
    }

    // Case 8: Unsupported method
    {
        Headers hdrs;
        hdrs["Host"] = "example.com";
        Request req(ControlData("FOO", "/test", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "FOO /test HTTP/1.1\r\nHost: example.com\r\n\r\n",
            req // Expected: invalid (method not standard)
        ));
    }

    // Case 9: No request target
    {
        Headers hdrs;
        hdrs["Host"] = "example.com";
        Request req(ControlData("GET", "", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "GET  HTTP/1.1\r\nHost: example.com\r\n\r\n",
            req // Expected: invalid (no path)
        ));
    }

    // Case 10: Header without value
    {
        Headers hdrs;
        hdrs["Host"] = "";
        Request req(ControlData("GET", "/test", "HTTP/1.1"), hdrs, "");
        cases.push_back(TestCase(
            "GET /test HTTP/1.1\r\nHost:\r\n\r\n",
            req // Expected: invalid (empty header value)
        ));
    }

    return cases;
}

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define TEST_PASSED "\033[32m" // Green
#define TEST_FAILED "\033[31m" // Red
void testRunner()
{
    testCases cases = getTestCases();
   
	for (testCases::const_iterator it = cases.begin(); it != cases.end(); ++it) {
		const TestCase& test = *it;
		try {
			Request req = validateRequest(test.raw);
            // std::cout << "Testing: " << test.raw << std::endl;
            // ControlData controlData = req.getControlData();
            // Headers headers = req.getHeaders();
            // std::cout << "Control Data: " << controlData.method << " "
            //             << controlData.requestTarget << " "
            //             << controlData.httpVersion << std::endl;
            // std::cout << "Headers: " << std::endl;  
            // for (Headers::const_iterator it = headers.begin(); it != headers.end(); ++it) {
            //     std::cout << "  " << it->first << ": " << it->second << std::endl;
            // }
            // std::cout << "Body: " << req.getBody() << std::endl;
            
			if (req == test.expected)
				std::cout << TEST_PASSED << "Test passed: \n" << RESET << test.raw << std::endl;
			else if (req.getErrorCode() != test.expected.getErrorCode())
				std::cout << TEST_FAILED << "Test failed: " << RESET << test.raw << std::endl;
            else
                std::cout << TEST_PASSED << "Test passed \n" << RESET << test.raw << std::endl;
		} catch (const std::exception& e) {
			std::cout << TEST_FAILED << "Exception caught for input: \n" << RESET << test.raw
						<< " - " << e.what() << std::endl;
		}
	}
}

int main () {
	testRunner();
	return 0;
}
