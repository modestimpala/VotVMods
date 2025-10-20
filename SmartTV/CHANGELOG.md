# 0.9.1

- Fix for users who don't have ffmpeg installed

# 0.9.0

- Added support for Audio Devices / Mic Capture
- Enhanced YT-DLP format support
  - Prioritizes combined a+v formats, attempts to use seperate a+v formats if combined not available.
- Fixed issue where removing a video that is the only video in the playlist would result in the video re-playing

# 0.8.2

- General UI, Playlist improvements
- Fixed some mediaplayer settings not saving properly 
- Sound classes changed again for 082c stable

# 0.8.1

- Potential fix for Pause Menu issue

# 0.8.0

- Added prop data saving
  - SmartTVs now save most media information including playlists, playtime, settings, etc.
  - Projectors save all lighting specific data.
- UI Improvements
  - Thumbnails
  - Track Time
  - Fixed some text issues
- Projector: 
  - Rotated root of Projector Mesh to face forward when holding
  - Projector can now be toggled with LMB and Open UI with RMB
- yt-dlp Improvements:
  - Requests UI to display current reuqest proccs and associated pipes, with ability to kill/clear requests
  - Added auto-downloader for yt-dlp from their [repo](https://github.com/yt-dlp/yt-dlp/releases/)
    - This avoids bundling the yt-dlp exe with the mod
    - The mod will automatically download yt-dlp into your Win64/yt-dlp dir
  - Added ability to change yt-dlp args in-game if needed
    - Please don't change these values unless you read their [readme](https://github.com/yt-dlp/yt-dlp/) beforehand


# 0.7.0

- Added Projector TV
  - Highly configurable, somewhat GPU intensive projector that uses 3 real simulated light sources on R G B channels to project media or devices.
- Added Smart Phone
  - A fully functioning mobile SmartTV.
  - Press T to turn on, LMB to raise, and RMB to open UI.
  - Smart Phones share one single main media player instance.

# 0.6.5

- Added dedicated Shuffle button
- Fixed sound issue

# 0.6.3

- Potential fix for Yt-dlp Pipe issue

# 0.6.2

- Added Looping Modes
- Added Seek Bar
- Added Portrait mode (settings)
- Added ability to attach plasma TV to walls
- Added Show/Hide button for Yt-Dlp path
- Adjusted Tooltips, Button text
- Optimized pipe usage

# 0.6.1

- Added volume slider
- Adjusted prop volumes and store size so they will always spawn inside box
- Adjusted widget so tick is disabled when not on OBS/ChatMon mode

# 0.6.0

- UI Overhaul
- Added Media Playback buttons
- Added Basic playlist support
- Added Device Mode
- Fixed Yt-Dlp issues 
- Can now play direct url files as well
- Adjustable widget size in settings UI
- Added Yt-Dlp log viewer

# 0.5.1 

- Fixed OBS Stream config settings
- Full YouTube support

# 0.5.0

- Initial Release