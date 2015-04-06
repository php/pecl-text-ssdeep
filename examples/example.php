<?php
/**
 *
 * php_ssdeep
 *
 * http://github.com/treffynnon/php_ssdeep
 *
 * A PHP extension to expose ssdeep functionality for fuzzy
 * hashing and comparing.
 *
 * Version 1.0.4
 *
 * BSD Licensed.
 *
 * Copyright (c) 2014, Simon Holywell
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

$string1 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla sed enim ante. Suspendisse eu massa ut libero congue aliquam. Morbi vehicula, lacus id faucibus ullamcorper, ante dui sodales velit, et laoreet nisl elit sed quam. Mauris quis purus odio, sed ornare urna. Sed eleifend sem ut nisl ultrices nec varius arcu malesuada. Quisque gravida mollis dictum. Nulla in neque vel mauris tincidunt lacinia ac placerat augue. Sed nec condimentum nisl. Integer congue leo nec elit sollicitudin placerat. Donec quis quam non erat ultricies lacinia. Sed sit amet massa vel dolor semper convallis vitae placerat lacus. Pellentesque ipsum erat, ultrices in mollis tincidunt, cursus sed justo. Nunc metus lectus, vehicula a gravida eget, venenatis sed elit.

Sed et nisl dolor, vitae interdum nulla. Donec egestas diam sit amet urna tincidunt elementum nec eu purus. Proin eget egestas enim. Pellentesque lobortis mattis orci id sodales. Nunc imperdiet bibendum enim vitae adipiscing. In.';

$string2 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla sed enim ante. Suspendisse eu massa ut libero congue aliquam. Morbi vehicula, lacus id faucibus ullamcorper, ante dui sodales velit, et laoreet nisl elit sed quam. Mauris quis purus odio, sed ornare urna. Sed eleifend sem ut nisl ultrices nec varius arcu malesuada. Quisque gravida mollis dictum. Nulla in neque vel mauris tincidunt lacinia ac placerat augue. Sed nec condimentum nisl. Integer congue leo nec elit sollicitudin placerat. Donec quis quam non erat ultricies lacinia. Sed sit amet massa vel dolor semper convallis vitae placerat lacus. Pellentesque ipsum erat, ultrices in mollis tincidunt, cursus sed justo. Nunc metus lectus, vehicula a gravida eget, venenatis sed elit.

Donec id porttitor sem. Vestibulum eu augue non enim feugiat bibendum eu pellentesque purus. Aenean tortor felis, tempor ullamcorper feugiat sed, convallis accumsan nunc. Cras sem justo, congue eu sollicitudin eget, vestibulum id ipsum. Vivamus pulvinar semper turpis ut lobortis. Nulla consequat ornare sem eu cursus. Suspendisse facilisis bibendum elit. Duis commodo condimentum dolor, nec mollis leo vulputate at. Morbi turpis elit, varius nec iaculis sit amet, suscipit vel turpis. Etiam faucibus, felis eget feugiat placerat, velit leo convallis diam, eget rhoncus elit quam in felis. Nunc condimentum purus at odio dictum nec hendrerit sapien placerat.

Mauris sit amet urna augue, ut fermentum tellus. Aliquam sit amet molestie arcu. Aenean sit amet sagittis nisl. Aenean eleifend tincidunt ipsum a commodo. Aliquam erat volutpat. Mauris venenatis, augue nec interdum pretium, libero diam venenatis massa, nec posuere libero metus in lorem. Quisque eget odio eget purus vulputate pharetra id ac quam. Aliquam.';

$file = __FILE__;

$hash1 = ssdeep_fuzzy_hash($string1);
 echo 'Hash 1: ' . $hash1 . "\n";

$hash2 = ssdeep_fuzzy_hash($string2);
echo 'Hash 2: ' . $hash2 . "\n";

$hash3 = ssdeep_fuzzy_hash_filename($file);
echo 'Hash 3: ' . $hash3 . "\n";

$match = ssdeep_fuzzy_compare($hash1, $hash2);
echo '1 & 2 Match:' . $match . "\n";

$match2 = ssdeep_fuzzy_compare($hash2, $hash3);
echo '2 & 3 Match:' . $match2 . "\n";
