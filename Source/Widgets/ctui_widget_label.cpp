#include "pch.h"

#include "ctui_widget_label.h"


#include "ctui_print.h"
#include "ctui_utf8.h"
#include "Grapheme/ctui_grapheme.h"
#include "Grapheme/ctui_graphemeview.h"

namespace 
{
	template<class... Ts>
	struct overloaded : Ts... {
		using Ts::operator()...;
	};

	template<class... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;
}

namespace ctui
{
	bool Label::input(Key key)
	{
		return false;
	}

	void Label::measure(int available_width)
	{
		// If _fill is active and a bounded width was given,
		// width starts at that available width (Label should fill the space).
		// Otherwise width starts at 0 and only grows from the text below.
		int width = (_fill && available_width != INT_MAX) ? available_width : 0, height = 0;

		size_t calc_available_width = _wraplength == 0 ? available_width : std::min(static_cast<size_t>(available_width), _wraplength);


		const auto lines = _text.raw_lines(calc_available_width);

		// Find the widest line of the text (accounting for
		// UTF-8 display width, e.g. multi-byte chars counted correctly).
		for (const std::string& line : lines)
		{
			width = std::max(width, static_cast<int>(utf8_display_width(line)));
		}

		// If a maximum available width is given, clamp width to it -
		// even if _fill raised it or the text is wider than allowed.
		if (available_width != INT_MAX)
			width = std::min(width, available_width);

		// Height = number of text lines, but at least kEmptyLabelHeight
		// (prevents a 0px tall label when the text is empty).
		height = static_cast<int>(std::max<size_t>(lines.size(), kEmptyLabelHeight));

		// Store computed bounds for the measure pass.
		_relative_bounds = Rect(
			width,
			height
		);
	}

	void Label::resolve_bounds(int startx, int starty)
	{
		_absolute_bounds = Rect(
			(_relative_bounds.x.value_or(0) + startx),
			(_relative_bounds.y.value_or(0) + starty),
			_relative_bounds.width.value(),
			_relative_bounds.height.value()
		);
	}

	void Label::render()
	{
		using ModVariant = std::variant<Color, GraphicMod>;

		if (!_absolute_bounds.has_values())
		{
			throw std::runtime_error("_absolute_bounds has not been initialized. Please call resolve_bounds() before render.");
		}

		std::vector<ModVariant> modStack;
		modStack.reserve(6);

		size_t line = 0, x_off = 0;
		int new_line = true;
		const auto raw_lines = _text.cached_raw_lines();
		for (const TextToken& tt : _text.get_buffer())
		{
			auto render_string = [&](const std::string& str)
				{
					for (Grapheme grapheme : GraphemeView(str))
					{
						if (grapheme.text == "\n")
						{
							x_off = 0;
							line++;
							new_line = true;
							continue;
						}

						size_t wraplength = _wraplength == 0 ? _absolute_bounds.width.value() : std::min(static_cast<size_t>(_absolute_bounds.width.value()), _wraplength);

						if (x_off + grapheme.terminal_width() > wraplength)
						{
							x_off = 0;
							line++;
							new_line = true;
						}

						size_t line_size = utf8_display_width(raw_lines[line]);
						size_t extra_off = 0;
						size_t box_width = _relative_bounds.width.value();

						if (_halign == Align::Center)
						{
							extra_off = (box_width > line_size) ? (box_width - line_size) / 2 : 0;
						}
						else if (_halign == Align::End)
						{
							extra_off = (box_width > line_size) ? (box_width - line_size) : 0;
						}

						if (!new_line)
						{
							print << grapheme.text;
						}
						else
						{
							print << mv_cursor(_absolute_bounds.x.value() + x_off + extra_off + 1,
								_absolute_bounds.y.value() + line + 1) <<
								grapheme.text;
							new_line = false;
						}

						x_off += grapheme.terminal_width(); // jetzt immer NACH Positionierung/Druck
					}

					// OLD:
					/* size_t start_byte = 0;
					while (start_byte < str.size())
					{
						unsigned int new_lines = 0;
						auto end_byte = str.find('\n', start_byte);
						std::string to_render = str.substr(start_byte);
						if (end_byte != std::string::npos)
						{
							to_render = str.substr(start_byte, end_byte - start_byte);
							++new_lines;
							start_byte = end_byte + 1;
						}
						else {
							start_byte = std::string::npos;
						}

						size_t line_size = utf8_display_width(raw_lines[cur_raw_line]);
						size_t extra_off = 0;
						size_t box_width = _relative_bounds.width.value();

						if (_halign == Align::Center)
						{
							extra_off = (box_width > line_size) ? (box_width - line_size) / 2 : 0;
						}
						else if (_halign == Align::End)
						{
							extra_off = (box_width > line_size) ? (box_width - line_size) : 0;
						}

						print <<
							mv_cursor(_absolute_bounds.x.value() + x_off + extra_off + 1,
								_absolute_bounds.y.value() + y_off + 1) <<
							to_render;

						x_off = new_lines ? 0u : x_off + utf8_display_width(to_render);
						y_off += new_lines;

						if (new_lines)
						{
							++cur_raw_line;
						}
					}*/
				};

			std::visit(overloaded{
				[&modStack](const Color& c)
				{
					modStack.emplace_back(c);
					print << c;
				},
				[&modStack](const GraphicMod& gm)
				{
					modStack.emplace_back(gm);
					print << gm;
				},
				[&](const std::string& str)
				{
					render_string(str);
				},
				[&](const std::function<std::string()>& fn)
				{
					render_string(fn());
				}
			}, tt);
		}
		print.exec();
	}
}
