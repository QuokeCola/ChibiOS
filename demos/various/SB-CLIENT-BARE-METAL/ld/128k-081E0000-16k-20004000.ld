/*
    ChibiOS - Copyright (C) 2006..2024 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * Sandbox memory setup.
 */
MEMORY
{
    flash0 (rx) : org = 0x081E0000, len = 128k
    ram0   (wx) : org = 0x20004000, len = 16k
}

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("CODE_SPACE", flash0);

/* RAM region to be used for data.*/
REGION_ALIAS("DATA_SPACE", ram0);
REGION_ALIAS("DATA_SPACE_LMA", flash0);

/* Generic rules inclusion.*/
INCLUDE rules.ld
