#include "pch.h"
#include "ctui_grapheme.h"

#include <utf8proc.h>
namespace ctui
{
	size_t Grapheme::byte_count() const
	{
		return text.size();
	}

	size_t Grapheme::terminal_width() const
	{
		utf8proc_int32_t codepoint;

		utf8proc_iterate(
			reinterpret_cast<const utf8proc_uint8_t*>(text.data()),
			static_cast<utf8proc_ssize_t>(text.size()),
			&codepoint
		);

		return static_cast<size_t>(utf8proc_charwidth(codepoint));
	}

}
