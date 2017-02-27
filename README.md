---
documentclass: physycomen
title:  "json_packer"
author: "Fabbri, Sinigardi"
---

<a href="http://www.physycom.unibo.it"> 
<div class="image">
<img src="https://cdn.rawgit.com/physycom/templates/697b327d/logo_unibo.png" width="90" height="90" alt="© Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna"> 
</div>
</a>
<a href="https://travis-ci.org/physycom/json_packer"> 
<div class="image">
<img src="https://travis-ci.org/physycom/json_packer.svg?branch=master" width="90" height="20" alt="Build Status"> 
</div>
</a>
<a href="https://ci.appveyor.com/project/cenit/json-packer"> 
<div class="image">
<img src="https://ci.appveyor.com/api/projects/status/4t0f1vp5e57krbry?svg=true" width="90" height="20" alt="Build Status"> 
</div>
</a>


### Purpose
This tool has been written in order to merge multiple .json files, in particular giving priority to our GNSS data format, keeping an ordered sequence of objects in the file.

### Installation
**make** and a **C++11** compatible compiler are required. Clone the repo and type ``make``, it should be enough in most cases to build the two executables!   
There's also a **VS2015** solution avalaible.   
Contains [jsoncons](https://github.com/danielaparker/jsoncons) and [nlohmannjson](https://github.com/nlohmann/json) as git submodules.

### Usage
```
packer_nlohmannjson.exe -o packed_name.json file1.json file2.json ... (to use the nlohmann's json library)
packer_jsoncons.exe -o packed_name.json file1.json file2.json ... (to use the danielaparker's json library)
```
In the former case you will use nlohmann's json library to parse input file and prepare output file, while in the latter jsoncons will be used.

More details about file formats is available [here](https://github.com/physycom/file_format_specifications/blob/master/formati_file.md).


