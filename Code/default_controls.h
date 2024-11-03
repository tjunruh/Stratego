#pragma once
#include <string>
#include <ascii_io.h>
#include <format_tools.h>

struct control_mapping
{
	std::string name = "";
	int key = ascii_io::undefined;
};

const std::vector<control_mapping> default_control_names =
{
	{"up", ascii_io::up},
	{"down", ascii_io::down},
	{"right", ascii_io::right},
	{"left", ascii_io::left},
	{"spy", ascii_io::s},
	{"flag", ascii_io::f},
	{"1", ascii_io::one},
	{"2", ascii_io::two},
	{"3", ascii_io::three},
	{"4", ascii_io::four},
	{"5", ascii_io::five},
	{"6", ascii_io::six},
	{"7", ascii_io::seven},
	{"8", ascii_io::eight},
	{"9", ascii_io::nine},
	{"bomb", ascii_io::b},
	{"select", ascii_io::enter},
	{"quit", ascii_io::q},
	{"new turn", ascii_io::space},
	{"finalize", ascii_io::enter},
	{"help", ascii_io::h},
	{"save", ascii_io::s},
	{"enable line drawing", 0},
	{"enable color", 0},
	{"background color", format_tools::black},
	{"foreground color", format_tools::white},
	{"cursor color", format_tools::green},
	{"cursor arrow color", format_tools::yellow},
	{"scout arrow color", format_tools::yellow},
	{"spy color", format_tools::blue},
	{"flag color", format_tools::magenta},
	{"1 color", format_tools::blue},
	{"2 color", format_tools::blue},
	{"3 color", format_tools::blue},
	{"4 color", format_tools::blue},
	{"5 color", format_tools::blue},
	{"6 color", format_tools::blue},
	{"7 color", format_tools::blue},
	{"8 color", format_tools::blue},
	{"9 color", format_tools::blue},
	{"bomb color", format_tools::cyan},
	{"hidden piece color", format_tools::red},
	{"bold foreground", 0}
};