#pragma once
#include "x64_gdb_stub_handler.hpp"

#include "../windows_emulator.hpp"

class win_x64_gdb_stub_handler : public x64_gdb_stub_handler
{
public:
	win_x64_gdb_stub_handler(windows_emulator& win_emu)
		: x64_gdb_stub_handler(win_emu.emu())
		  , win_emu_(&win_emu)
	{
	}

	gdb_action cont() override
	{
		try
		{
			this->win_emu_->start();
		}
		catch (const std::exception& e)
		{
			puts(e.what());
		}

		return gdb_action::resume;
	}

	gdb_action stepi() override
	{
		try
		{
			this->win_emu_->start({}, 1);
		}
		catch (const std::exception& e)
		{
			puts(e.what());
		}

		return gdb_action::resume;
	}

private:
	windows_emulator* win_emu_{};
};
