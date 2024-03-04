# Simple-Static-WebServer

NOTES:
- Multi-threaded server
- Use HTTP 0.9
- Windows only

Program Flow:
- Read configuration from a specified config file (Basic Configuration)
- Wait for incoming requests
- Parse the incoming request
- Take the path and intrepret it so that we can map it to a file or a directory
- If it's a file:
  - Read the file content (if have suffcient permissions)
  - Return the file content as the response body
- If it's a directory:
  - Read the directories within the path specified in the url (if have suffcient permissions)
  - Load an html template saved in a pre-configured directory
  - Replace the following token with the directory listing %BODY%
  - Return that String as the response body


Components:
-Config Reader
-Network Layer (Multi-Threaded Server)
-Request Parser
-File Reader
-Directory Reader
-Response Dumper