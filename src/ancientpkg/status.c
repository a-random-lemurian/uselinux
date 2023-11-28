#include <stdlib.h>
#include <string.h>

char* status_string(int status)
{
    char *out = malloc(320);
    switch (status)
    {
        case 100: strcpy(out, "100 Continue"); break;
        case 101: strcpy(out, "101 Switching Protocols"); break;
        case 102: strcpy(out, "102 Processing"); break;
        case 103: strcpy(out, "103 Early Hints"); break;
        case 200: strcpy(out, "200 OK"); break;
        case 201: strcpy(out, "201 Created"); break;
        case 202: strcpy(out, "202 Accepted"); break;
        case 203: strcpy(out, "203 Non-Authoritative Information"); break;
        case 204: strcpy(out, "204 No Content"); break;
        case 205: strcpy(out, "205 Reset Content"); break;
        case 206: strcpy(out, "206 Partial Content"); break;
        case 207: strcpy(out, "207 Multi-Status"); break;
        case 208: strcpy(out, "208 Already Reported"); break;
        case 226: strcpy(out, "226 IM Used"); break;
        case 300: strcpy(out, "300 Multiple Choices"); break;
        case 301: strcpy(out, "301 Moved Permanently"); break;
        case 302: strcpy(out, "302 Found"); break;
        case 303: strcpy(out, "303 See Other"); break;
        case 304: strcpy(out, "304 Not Modified"); break;
        case 307: strcpy(out, "307 Temporary Redirect"); break;
        case 308: strcpy(out, "308 Permanent Redirect"); break;
        case 400: strcpy(out, "400 Bad Request"); break;
        case 401: strcpy(out, "401 Unauthorized"); break;
        case 402: strcpy(out, "402 Payment Required"); break;
        case 403: strcpy(out, "403 Forbidden"); break;
        case 404: strcpy(out, "404 Not Found"); break;
        case 405: strcpy(out, "405 Method Not Allowed"); break;
        case 406: strcpy(out, "406 Not Acceptable"); break;
        case 407: strcpy(out, "407 Proxy Authentication Required"); break;
        case 408: strcpy(out, "408 Request Timeout"); break;
        case 409: strcpy(out, "409 Conflict"); break;
        case 410: strcpy(out, "410 Gone"); break;
        case 411: strcpy(out, "411 Length Required"); break;
        case 412: strcpy(out, "412 Precondition Failed"); break;
        case 413: strcpy(out, "413 Content Too Large"); break;
        case 414: strcpy(out, "414 URI Too Long"); break;
        case 415: strcpy(out, "415 Unsupported Media Type"); break;
        case 416: strcpy(out, "416 Range Not Satisfiable"); break;
        case 417: strcpy(out, "417 Expectation Failed"); break;
        case 421: strcpy(out, "421 Misdirected Request"); break;
        case 422: strcpy(out, "422 Unprocessable Content"); break;
        case 423: strcpy(out, "423 Locked"); break;
        case 424: strcpy(out, "424 Failed Dependency"); break;
        case 425: strcpy(out, "425 Too Early"); break;
        case 426: strcpy(out, "426 Upgrade Required"); break;
        case 428: strcpy(out, "428 Precondition Required"); break;
        case 429: strcpy(out, "429 Too Many Requests"); break;
        case 431: strcpy(out, "431 Request Header Fields Too Large"); break;
        case 451: strcpy(out, "451 Unavailable for Legal Reasons"); break;
        case 500: strcpy(out, "500 Internal Server Error"); break;
        case 501: strcpy(out, "501 Not Implemented"); break;
        case 502: strcpy(out, "502 Bad Gateway"); break;
        case 503: strcpy(out, "503 Service Unavailable"); break;
        case 504: strcpy(out, "504 Gateway Timeout"); break;
        case 505: strcpy(out, "505 HTTP Version Not Supported"); break;
        case 506: strcpy(out, "506 Variant Also Negotiates"); break;
        case 507: strcpy(out, "507 Insufficient Storage"); break;
        case 508: strcpy(out, "508 Loop Detected"); break;
        case 511: strcpy(out, "511 Network Authentication Required"); break;
        default:  strcpy(out, "[Error: UNKNOWN CODE]"); break;
    }

    return out;
}
