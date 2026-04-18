# Developer File Organizer CLI
A command-line tool written in C that automatically organizes messy folders. Reads all directory contents one by one and changes the file path to an appropriate folder based on the file extension.

## How to run
The program has 2 modes, Preview mode for changes made to directory without moving files or creating folders, and Organize mode for relocating files to appropriate folders based on file extension.

Preview mode:  
```bash
./organizer --preview /folder
```

Organize mode: 
```bash
./organizer /folder
```

## Categories and file extensions 
The program has 6 categories that stores files with certain file extensions.

Categories:
 - Images .jpg .jpeg .png
 - Documents .pdf .doc .docx .xls .xlsx .ppt .pptx .odt .txt rtf
 - Music .mp3 .wav .m4a
 - Videos .mp4 .mov .mkv .wmv
 - Code .py .java .c .cpp .cc .cs .swift .go .rs .js
 - Other (Files with no extensions or unsupported extensions)

## Examples
Preview mode: 

 Input: 
 ```bash
 ./organizer --preview /mnt/c/test_folder
 ```

 Output: 
 ```text
Preview: /mnt/c/test_folder
 app.cpp -> /mnt/c/test_folder/Code
 audio.wav -> /mnt/c/test_folder/Music
 budget.xls -> /mnt/c/test_folder/Documents
 clip.mp4 -> /mnt/c/test_folder/Videos
 document.rtf -> /mnt/c/test_folder/Documents
 essay.docx -> /mnt/c/test_folder/Documents
 game.cs -> /mnt/c/test_folder/Code
 graphic.png -> /mnt/c/test_folder/Images
 image.jpeg -> /mnt/c/test_folder/Images
 index.js -> /mnt/c/test_folder/Code
 ios.swift -> /mnt/c/test_folder/Code
 letter.doc -> /mnt/c/test_folder/Documents
 lib.rs -> /mnt/c/test_folder/Code
 main.c -> /mnt/c/test_folder/Code
 module.cc -> /mnt/c/test_folder/Code
 movie.mov -> /mnt/c/test_folder/Videos
 mystery.xyz -> /mnt/c/test_folder/Other
 noextension -> /mnt/c/test_folder/Other
 notes.odt -> /mnt/c/test_folder/Documents
 photo.jpg -> /mnt/c/test_folder/Images
 presentation.pptx -> /mnt/c/test_folder/Documents
 program.java -> /mnt/c/test_folder/Code
 readme.txt -> /mnt/c/test_folder/Documents
 recording.wmv -> /mnt/c/test_folder/Videos
 report.pdf -> /mnt/c/test_folder/Documents
 script.py -> /mnt/c/test_folder/Code
 server.go -> /mnt/c/test_folder/Code
 slides.ppt -> /mnt/c/test_folder/Documents
 song.mp3 -> /mnt/c/test_folder/Music
 spreadsheet.xlsx -> /mnt/c/test_folder/Documents
 video.mkv -> /mnt/c/test_folder/Videos
Preview: would organize 31 files!
```

Organize mode:

 Input: 
 ```bash
 ./organizer /mnt/c/test_folder
 ```

 Output: 
 ```text
Organizing: /mnt/c/test_folder
 app.cpp -> /mnt/c/test_folder/Code
 audio.wav -> /mnt/c/test_folder/Music
 budget.xls -> /mnt/c/test_folder/Documents
 clip.mp4 -> /mnt/c/test_folder/Videos
 document.rtf -> /mnt/c/test_folder/Documents
 essay.docx -> /mnt/c/test_folder/Documents
 game.cs -> /mnt/c/test_folder/Code
 graphic.png -> /mnt/c/test_folder/Images
 image.jpeg -> /mnt/c/test_folder/Images
 index.js -> /mnt/c/test_folder/Code
 ios.swift -> /mnt/c/test_folder/Code
 letter.doc -> /mnt/c/test_folder/Documents
 lib.rs -> /mnt/c/test_folder/Code
 main.c -> /mnt/c/test_folder/Code
 module.cc -> /mnt/c/test_folder/Code
 movie.mov -> /mnt/c/test_folder/Videos
 mystery.xyz -> /mnt/c/test_folder/Other
 noextension -> /mnt/c/test_folder/Other
 notes.odt -> /mnt/c/test_folder/Documents
 photo.jpg -> /mnt/c/test_folder/Images
 presentation.pptx -> /mnt/c/test_folder/Documents
 program.java -> /mnt/c/test_folder/Code
 readme.txt -> /mnt/c/test_folder/Documents
 recording.wmv -> /mnt/c/test_folder/Videos
 report.pdf -> /mnt/c/test_folder/Documents
 script.py -> /mnt/c/test_folder/Code
 server.go -> /mnt/c/test_folder/Code
 slides.ppt -> /mnt/c/test_folder/Documents
 song.mp3 -> /mnt/c/test_folder/Music
 spreadsheet.xlsx -> /mnt/c/test_folder/Documents
 video.mkv -> /mnt/c/test_folder/Videos
Successfully organized 31 files!
```
