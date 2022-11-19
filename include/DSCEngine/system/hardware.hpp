#pragma once

namespace DSC::Hardware
{		
	typedef short ExtendedPalette[256];

	namespace MainEngine
	{
		inline static short* const BgPalette  = (short* const)0x05000000;
		inline static short* const ObjPalette = (short* const)0x05000200;
		
		inline static short* const Oam        = (short* const)0x07000000;
		
		inline static short* const BgVram     = (short* const)0x06000000;
		inline static short* const ObjVram    = (short* const)0x06400000;
		
		//inline static ExtendedPalette* const BgExtPalette = (ExtendedPalette* const);
	}
	
	namespace SubEngine
	{
		inline static short* const BgPalette  = (short* const)0x05000400;
		inline static short* const ObjPalette = (short* const)0x05000600;
		
		inline static short* const Oam        = (short* const)0x07000400;
		
		inline static short* const BgVram     = (short* const)0x06200000;
		inline static short* const ObjVram    = (short* const)0x06600000;		
	}	
	
	extern char* const BanksReg;
		
	class VramBank
	{
	private:
		char bank_name; // 'A'..'I'				
		bool is_lcd = true;
		bool is_main = true;
		bool is_background = true;		
		bool is_vram = true;
		int ofs = 0;		
		
		char backup = 0;
	public:
		VramBank(char bank_name);
		
		VramBank& lcd();
		
		VramBank& main();
		VramBank& sub();
		
		VramBank& background();
		VramBank& sprite();
		
		VramBank& vram();
		VramBank& ext_palette();
		
		VramBank& slot(int slot_number);
				
		void config();
		
		void enable();
		void disable();
		
		VramBank& save_state();
		void restore();
	};
	
}