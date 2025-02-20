<p align="center" width="100%">

<img src="https://www.dropbox.com/scl/fi/9m5z6o95m7l8101mizb4e/chatmon.png?rlkey=d0sukwkq81o6gq06torjrd2ov&st=2avzpi0v&dl=1">

</p>


<p align="center" width="100%">
<a href="https://discord.gg/Bq7HCMRfjk"><img width="5%" src="https://www.dropbox.com/scl/fi/96uoyd529gq617880m0cu/636e0a6a49cf127bf92de1e2_icon_clyde_blurple_RGB.png?rlkey=343xgtya1h3r53bblx8lns473&st=ih0q2alh&dl=1"></a>
</p>


# SmartTV

Readme is WIP

SmartTV is a mod that allows you to watch YouTube, Vimeo/Twitch CLIP videos ([and more](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md)) display OBS Source output and also display your Twitch Chat in-game.

Props
- Monitor SmartTV
- Medium SmartTV
- Plasma SmartTV

Modes
- ChatMon
- OBS Source Output
- Media



## OBS Source Setup

Enable Websocket Server on OBS 

Tools > WebSocket Server Settings > Enable WebSocket server 

No password is default on the viewer, with port 4455. Enable and apply/ok.

In-game, configure your settings appropriately. Source must be Source name *exactly*, e.g. "Game Capture" -> Rename to VotVOBS or "Display Capture" -> Rename to VotVOBS

OBS Mode does not handle audio, it is Source video output *only*



**This does NOT allow you to watch Twitch streams in-game still.** You can watch YouTube, Vimeo, Twitch CLIPS, [and more](https://github.com/yt-dlp/yt-dlp/blob/master/supportedsites.md). Otherwise, chat viewer simply displays Twitch chat with emotes, nothing more. 

