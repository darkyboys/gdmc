# GDMC - Goblin's Demonic Mouse Controler ❤️‍🔥
`GDMC` is an *Open Source - Linux Program* for allowing gamers to set their *Mouse Debounce Time To 0* with the help of different backends available for gamers to chose from.

## What exactly is GDMC?
`GDMC` itself is just a wrapper / UI Client for the backends it provides, It also autoinstalls these backends and manages them for the users so they don't even need to dig into these backend's Command Line interface just to get their Mouse Debounce To Lowest possible value!

## How GDMC Works ?
`GDMC` uses the 2 different backends which gamers can select from!
 - **DCI-D** : An insanely good debounce controler for those who wants to click as fast as possible! (Eg: Drag clickers)
 - **PvPGod Mouse** : Best for those who wants to click insanely fast but also takes a little more time in between key presses (Eg: Butterfly clickers , Jitter Clickers)

These programs works by sending all the clicks registered by your mouse physically to your kernel as `"Virtual Clicks"`. Let's see how!

<p>When ever you presses a button in your mouse it vibrates and the vibration don't just causes a single click but multiple clicks on the actual switch which registers the clicks , So due to this when you click once the clicks registered are actually double or tripple due to the vibration and to counter this behaviour the companies uses the Debounce Time in their mouse. A Debounce time is nothing but a time in which any clicks registered will be ignored by your software (Might be firmware or just software drivers) so due to this time when you click once , all the mistakenly registered clicks are ignored at the software level. </p>

<p>Now here comes these backends to play! Your desktop might get the cut down clicks but your kernel sees all the clicks unless the debounce time is at firmware level so these backends just uses the kernel to see the clicks and then they just selects a few clicks from those physical clicks and sends them as virtual clicks so that it simulates the low debounce time!</p>

## Why don't these backends sends all the clicks as virtual clicks
These backends don't sends all the clicks they see as virtual clicks because it would also register same click twice meaning let up suppose you clicked once but physically they were 3 clicks in total so if we send all these clicks then they would be 3 right ? But 1 of them was the click already registered by your Desktop Client which means acutal clicks needed to be send are just 2 not 3 , Which is why they are super accurate at sending clicks.

## Do they use different algorithms ?
Yes, both `DCI-D` and `PvPGod Mouse` uses different algorithms! And both are optimized for different types of clickers. Let's take a look at them

 - **DCI-D**: This stands for `Double Clicker Injector` and it checks all the clicks you are doing physically , It also takes a number of clicks which your Desktop client can register (Leave it to 9 if you don't know your current CPS, 9 is universal for every mouse) And according to that number it generates a time in which if you click twice then it will register a virtual click from the kernel, Meaning if you click twice rapidly then it will be 3 cicks not 2, And this is superb for those who clicks super fast as it can benifit players from insanely high cps (But under the human possibliy , Usually it can go up to 17 - 20 cps if your cps before was even lower than 10)

 - **PvPGod Mouse**: This stands for it's name lol but this one is slightly different , Because unlike `DCI-D` This will only check the first 2 clicks when you start clicking and if you click rapidly then it will send all the clicks it sees at the kernel level to your desktop client , Which is why this one can register insanely high cps for those who can't click as fast as possible because this one never limits and it will send all the clicks your mouse is physically doing , But it is also why it is not suitable for rapid clickers who clicks at insane speeds because your first 2 clicks will only matter and if you click super fast then`PvPGod Mouse` will start sending all the clicks but if they are super fast then it's very possible that your debounce controler will block them anyways , Affecting the CPS Negatively. So if you can't click at insane speeds like a drag clicker then this might result in lower cps , But if you are clicking with gaps like butterfly clicking or jitter clicking then this might be your best friend for ever, Because it can blast up to (24 cps on butterfly).

 > Note that the cps number i have shown you are from my mouse and they will differ on mouse to mouse , My mouse is HyperX Haste 2 as of now while writing this.

## Are these hacks ?
No, They are just debounce time simulators / controlers and they are not hacks because they can only send those clicks which your mouse is actually registering at the kernel level , They are not going to spam clicks for you or make your aim better , They will just send those clicks which your mouse makes but your desktop client ignores via a condition. Although misusing these will be consider unfair play (I mean if you run `GDMC` 2 Instances together then they might explode the CPS Like insane which may provide you the unfair advantage and servers can ban you for doing those things).

## What are instances in GDMC ?
`Instances` are nothing but a number which tells `GDMC` about how many backends to activate! (Min:1 , Max: 2) 
 - In Simple Language if the Instance is set to 1 then it will lower the debounce time by 50% and if it is set to 2 then it will set the debounce time to abnsolute 0 (Setting debounce means simulation btw) Which reason of max 2 is because debouce can't be negative. 
 - 2 means more cps and 1 means more cps but less compared to 2. (50% cps + , 50% cps -)

## Is GDMC Available for windows ?
No, `GDMC` as a part of being `FOSS` and Community project using those backend which uses Linux's `libuinput` can't be run on Windows , Not even with `WSL` properly.

## How To Install GDMC ?
Installation is straight forward just make sure that you have the following packages installed already:-
 - Gtk3 
 - Webkit2gtk4
 - Cook build system (This is my project so you can install it from [here](https://github.com/darkyboys/cook))

And you are good to go just run these commands in your terminal:
```bash
mkdir ~/gdmc
git clone https://github.com/darkyboys/gdmc.git ~/gdmc
cd ~/gdmc
cook
sudo cook install
cd ~
rm -rf gdmc
```

And then when ever you want to run GDMC you can just launch a terminal and execute `gdmc` in it and it will automatically launch the GUI for you.

## Wanna Contribute ?
Ez just make your contribution and make a pull request by forking it and sit back , Have a nice coffee.

Thanks for reading i know y'all are going to troll kid 😹 on pvp servers