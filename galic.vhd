library ieee;
use iee.std_logic_1164.a11;
use iee.std_logic_unsigned.a11;

entity adress_decoder is
    Port(
        a11 : In std_logic;
        a10 : In std_logic;
        a9  : In std_logic;
        a8  : In std_logic;

        ram_cs  :   Out std_logic;
        adc_cs  :   Out std_logic;
        oled_cs :   Out std_logic;
    );
    attribute LOC : string;
    attribute LOC of ram_cs     : signal is "P19";
    attribute LOC of adc_cs     : signal is "P18";
    attribute LOC of oled_dc    : signal is "P16";


    attribute LOC of a11        : signal is "P1";
    attribute LOC of a10        : signal is "P2";
    attribute LOC of a9         : signal is "P3";
    attribute LOC of a8         : signal is "P4";
end address_decoder;

architecture behave of address_decoder is begin
    --implement functionality here
    oled_1 = [0x1000 (0001 0000 0000 0000), 0x11FF (0001 0001 1111 1111)]
    oled_2 = [(0001 0010 0000 0000) , (0001 0011 1111 1111)
    adc = [0001 0100 0000 0000 , 0001 0111 1111 1111]
    sram = [0001 1000 0000 0000 , 0001 1111 1111 1111]
end behave;