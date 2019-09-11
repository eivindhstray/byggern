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
    attribute LOC of oled_cs     : signal is "P17";
    attribute LOC of oled_dc    : signal is "P16";


    attribute LOC of a11        : signal is "P1";
    attribute LOC of a10        : signal is "P2";
    attribute LOC of a9         : signal is "P3";
    attribute LOC of a8         : signal is "P4";
end address_decoder;

architecture behave of address_decoder is begin
    --implement functionality here
    oled_cs <= a11 or a10 or a9;
    oled_dc <= a11 or a10 or not a9;
    adc_cs <= a11 or not a10;
    ram_cs <= (a11);
end behave;