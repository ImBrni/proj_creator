# proj_creator

This is a school project for one of my classes, its goal is to create a starting file for a couple of programming projects, it is written in C as per the requirements

# Usage

Print out help message with available templates and arguments: `proj_creator` or `proj_creator -h`

Print out version number: `proj_creator -v`

Create file with default name: `proj_creator <template>`

Do not create the template just print it to stdou: `proj_creator -o <template>`

Custom name for the output file: `proj_creator -n <custom_name_of_file_with_extension> <template>`

# Building

The repository contains a single Makefile, to build the project execute this command:
`make`
(The executable will be in the bin folder)

To build and run execute:
`make run`

# Installation

You can install this program to convenient location on you filesystem, as long as you can execute it
