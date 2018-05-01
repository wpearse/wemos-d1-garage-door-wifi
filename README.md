# Installation

Set three options at the top of the source file:

1. WiFi SSID to connect to
2. Password for the WiFi
3. Name of this garage door (you'll use this to access the web page)

Download this code to the Wemos D1. Wire the pushbutton input on the garage door the relay's contacts (in my case, the two NO contacts).

# Use

Once the D1 is installed and connected to wifi visit _name-of-garage-door.local_ in a browser. Hit the toggle link to active the garage door.

# Gotchas

- https://news.ycombinator.com/item?id=16964907
- Assumption is that you're using the Wemos relay shield
