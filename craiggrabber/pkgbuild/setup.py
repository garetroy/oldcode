import os
from setuptools import setup

# Utility function to read the README file.
# Used for the long_description.  It's nice, because now 1) we have a top level
# README file and 2) it's easier to type in the README file than to put a raw
# string in below ...
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

setup(
    name = "craiggrabber",
    version = "1.0",
    author = "Garett Roberts",
    author_email = "mygarett@gmail.com",
    description = ("A Craiglist Scraper that downloads all post info from a specified page"),
    license = "MIT",
    keywords = "craiglist craiggrabber scraper",
    url = "https://github.com/garetroy/craiggrabber",
    packages=["Beautifulsoup4", "requests"],
    long_description=read('README'),
    classifiers=[
        "Development Status :: Alpha",
        "Topic :: Utilities",
        "License :: OSI Approved :: MIT License",
    ],
)