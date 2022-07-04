# To-Do List

There were several features I wanted to add, but due to time and flash memory constraints, I couldn't.

## Features

### Rotating Things

There were two features that would require rotating the screen image an arbitrary number of degrees. However, the `setRotation()` method [only allows for four choices](https://learn.adafruit.com/adafruit-gfx-graphics-library/rotating-the-display?view=all#rotating-the-display=): 0, 90, 180 and 270 degrees. I wanted to do a roulette wheel and my [dice coin](https://d20key.com/#/coin) this way. But I may still do these using individual images at some point.

### Animated Things

I was hoping I could do GIF animations, but the CPU just can't handle it. Just loading the static JPEGs takes almost 300ms each.

### D&D Dice

I really wanted to add a d20, but again, I ran out of time and flash memory space. I may create a branch for this eventually. I even have all the images (from [these GIFs](https://d20key.com/#/) I created for my passphrase site).

It would have been cool to do other D&D dice, too: d4, d8, and d10 mainly.

### Interactivity

The coolest DEF CON badges allow you to interact with others. I considered trying to do some sort of head-to-head blackjack, but wasn't sure how I'd make that work. I considered generating a QR code that would take you to a website, too.