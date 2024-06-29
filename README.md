# AI Visualizer

This application allows visualizing the activation of different parts of an AI network 
as data is passed through it. This is based on the idea of AI models being built from
combinations of layers that data is fed through. The outputs of each layer can then be
inspected and displayed in a way that befits the layer type. 

This does not train a model, but can take in an already created model saved from 
PyTorch. This utilizes a utility in the fdeep library to convert the keras output
format to an representation that the fdeep C++ library can ingest. 

## Requirements

(Testing is done with MINGW 64-bit on Windows 10)

- Qt 6 (tested on 6.6.2)
- [Frugally Deep (fdeep)](https://github.com/Dobiasd/frugally-deep) 
- [Eigen](https://gitlab.com/libeigen/eigen) (Linear algebra library used by Fdeep)

## Architecture

The project is broken into a few libraries and the main application. These are split 
into the following directories:

- **application** - GUI application and main executable for interacting and viewing 
                    the models
- **viewmodels** - Qt QML module containing QML views and the Qt mdoels that expose
                   the underlying data to the QML
- **interface** - Classes defining the bridge between the underlying model 
                  representation and the front end viewmodels
- **impl** - Implementation of bridge to interact with underlying model implementations
	- **fdeepbridge** - Specific implementation to interact with Fdeep models
- **common** - Commonly included source files accross multiple of the previous items
- **test** - Integration level tests to full load of an AI model and creation of
             corresponding ViewModels
        
The purpose of the separation is to decouple the front end and back end implementations,
and leave the opportunity to support other underlying model representations in the future.
In addition, the **fdeepbridge** and **viewmodels** libraries use registries to be able
to select the proper layer classes, models, and views such that they could be chosen 
dynamically. This way, adding or replacing layer representations and view can be done 
outside of the libraries (although may still need them as dependencies).

## Current work in progress
- [x] implement dense layer view
- [ ] implement convolutional layer 
- [ ] Create application
	- [ ] select and load model file
	- [ ] select and load a data file
	- [ ] run data and interact and view model

## Needed Improvements
- Optimization. Currently, the needs of the interface are being shaken out. As that 
  settles it would be good to optimize how certain items are accessed to minimize data
  copying. The main trade off of over optimization would be inflexibility. It could be
  much faster to remove the bridge/interface to directly interact with the Eigen
  container classes used by Fdeep, but this would introduce heavy coupling. The
  downside is copying/converting the stored data to std::vectors for a more generic
  representation.
- More layer types need to be implemented. Currently only dense layers are supported.
- Package python as well and allow the application to directly select the keras 
  format and do the fdeep conversion python step automatically.
- Fix 3rdparty submodules. Some are no-longer used and frugally deep should be built
  and installed separately
- Naming. Some items need updated names (like tst_annrepresentation), and some need
  consistency (i.e. FdeepBridge::DenseLayer and FdeepBridge::FdeepUnknownLayer)

## Notes and Limitations
- This is a pet project so most items are minimally implemented, and progress is slow,
  and the git usage isn't to the level you can expect in industry.
- Eigen is a fairly large, header only library so compilation times can be long. MINGW
  requires the `-mbig-obj` option to support the size of certain generated objects.
- **Does this support GPT?** Not really. Some of the layer types GPT uses are 
  implemented (mainly dense layers), however thought would have to be put in to determine
  how best to display layers such as the decode and "attention" layers. Additionally,
  many passes through the network may occur for a given answer. This format works well
  for looking at convolutional neural nets where filter layers and their outputs can
  be easily visually interpreted, as well as fully connected layers, which can be visualized 
  as nodes "lighting up" as they are activated by a given input datum.
