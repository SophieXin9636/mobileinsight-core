MobileInsight
==============


# Introduction #

MobileInsight is a cross-platform package for mobile network monitoring and analysis on end device. It is developed by UCLA Wireless Networking Group (WiNG) and OSU Mobile System, Security and Networking (MSSN) lab, licensed under Apache Licence 2.0.

MobileInsight provides low-level monitors for mobile network, and extensible event-driven analyzers for major cellular protocols, such as radio resource control (RRC), mobility management (EMM), and session management (ESM). You can also define your own analyzers for customized usage.


Typical usage of MobileInsight consists of declaring a monitor to track the network status and calling ananlyzer for online/offline analysis. See [overview](http://metro.cs.ucla.edu/mobile_insight/overview.html) on how this works, and [examples](http://metro.cs.ucla.edu/mobile_insight/examples.html) on how to use it.


# Installation #

Please see [here](http://metro.cs.ucla.edu/mobile_insight/get_started.html) for more detailed instructions. The following is a quick summary of installation:

First install [Python 2.7](https://www.python.org/) if you do not have it.

Second, MobileInsight builds on top of `pyserial` and `crcmod`, so please install both libraries, for example, using `pip`:

    pip install pyserial
    pip install crcmod

Then download MobileInsight and unpack the code:

    tar -zxvf MobileInsight-2.1.1.tar.gz
    cd MobileInsight-2.1.1

For macOS users, install MobileInsight using:

    ./install-macos.sh

It will automatically run an offline analysis example at the end.

For Linux and Windows users, install MobileInsight using:

    python setup.py install

To run MobileInsight GUI, please install the following Python libraries:

    pip install wxPython
    pip install matplotlib
