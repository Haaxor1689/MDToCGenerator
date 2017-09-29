# MDToCGenerator

## Description

Simple QT console application for generating table of contents for mardown files.

## Usage
Execatubla takes one argument, the name of markdown file you want to generate table of contents for. Output is new markdown file named ${filename}_ToC.md.

```bash
./generateToC file.md
```

## Example

Input `example.md`:

```md
# Title A
## Title B

Text Text Text Text Text Text 

## Title A

Text Text Text Text Text Text Text Text

# Title
```

Output `example_ToC.md`:

```md
* [Title A](#title-a)
	* [Title B](#title-b)
	* [Title A](#title-a-1)
* [Title](#title)
```
