--TEST--
Test ssdeep fuzzy hashing functions
--FILE--
<?php
$string1 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla sed enim ante. Suspendisse eu massa ut libero congue aliquam. Morbi vehicula, lacus id faucibus ullamcorper, ante dui sodales velit, et laoreet nisl elit sed quam. Mauris quis purus odio, sed ornare urna. Sed eleifend sem ut nisl ultrices nec varius arcu malesuada. Quisque gravida mollis dictum. Nulla in neque vel mauris tincidunt lacinia ac placerat augue. Sed nec condimentum nisl. Integer congue leo nec elit sollicitudin placerat. Donec quis quam non erat ultricies lacinia. Sed sit amet massa vel dolor semper convallis vitae placerat lacus. Pellentesque ipsum erat, ultrices in mollis tincidunt, cursus sed justo. Nunc metus lectus, vehicula a gravida eget, venenatis sed elit.

Sed et nisl dolor, vitae interdum nulla. Donec egestas diam sit amet urna tincidunt elementum nec eu purus. Proin eget egestas enim. Pellentesque lobortis mattis orci id sodales. Nunc imperdiet bibendum enim vitae adipiscing. In.';

$string2 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla sed enim ante. Suspendisse eu massa ut libero congue aliquam. Morbi vehicula, lacus id faucibus ullamcorper, ante dui sodales velit, et laoreet nisl elit sed quam. Mauris quis purus odio, sed ornare urna. Sed eleifend sem ut nisl ultrices nec varius arcu malesuada. Quisque gravida mollis dictum. Nulla in neque vel mauris tincidunt lacinia ac placerat augue. Sed nec condimentum nisl. Integer congue leo nec elit sollicitudin placerat. Donec quis quam non erat ultricies lacinia. Sed sit amet massa vel dolor semper convallis vitae placerat lacus. Pellentesque ipsum erat, ultrices in mollis tincidunt, cursus sed justo. Nunc metus lectus, vehicula a gravida eget, venenatis sed elit.

Donec id porttitor sem. Vestibulum eu augue non enim feugiat bibendum eu pellentesque purus. Aenean tortor felis, tempor ullamcorper feugiat sed, convallis accumsan nunc. Cras sem justo, congue eu sollicitudin eget, vestibulum id ipsum. Vivamus pulvinar semper turpis ut lobortis. Nulla consequat ornare sem eu cursus. Suspendisse facilisis bibendum elit. Duis commodo condimentum dolor, nec mollis leo vulputate at. Morbi turpis elit, varius nec iaculis sit amet, suscipit vel turpis. Etiam faucibus, felis eget feugiat placerat, velit leo convallis diam, eget rhoncus elit quam in felis. Nunc condimentum purus at odio dictum nec hendrerit sapien placerat.

Mauris sit amet urna augue, ut fermentum tellus. Aliquam sit amet molestie arcu. Aenean sit amet sagittis nisl. Aenean eleifend tincidunt ipsum a commodo. Aliquam erat volutpat. Mauris venenatis, augue nec interdum pretium, libero diam venenatis massa, nec posuere libero metus in lorem. Quisque eget odio eget purus vulputate pharetra id ac quam. Aliquam.';

$file1 = dirname(__FILE__) . '/test1.data';
$file2 = dirname(__FILE__) . '/test2.data';
file_put_contents($file1, $string1 . $string2);
file_put_contents($file2, $string2 . $string1);

$hash1 = ssdeep_fuzzy_hash($string1);
var_dump($hash1);

$hash2 = ssdeep_fuzzy_hash($string2);
var_dump($hash2);

$hash3 = ssdeep_fuzzy_hash_filename($file1);
var_dump($hash3);

$hash4 = ssdeep_fuzzy_hash_filename($file2);
var_dump($hash4);

$match = ssdeep_fuzzy_compare($hash1, $hash2);
var_dump($match);

$match2 = ssdeep_fuzzy_compare($hash2, $hash3);
var_dump($match2);

$match3 = ssdeep_fuzzy_compare($hash3, $hash4);
var_dump($match3);
?>
--CLEAN--
<?php
$file1 = dirname(__FILE__) . '/test1.data';
$file2 = dirname(__FILE__) . '/test2.data';
unlink($file1);
unlink($file2);
?>
--EXPECT--
string(78) "24:FPlUMKVsgNfgmjFadP6WboWjb8tsH4RSXqMbLFpjwPDt4tFF:9lUajiiPbbnr4RSXqMbppMZ4t3"
string(76) "48:9lUajiiPbbnr4RSXqMbLbmo03Rcq0K/cvhQ+3/M8M5BEaB6:9HFHsGqabmoMR18hQ+308sBdk"
string(100) "48:9lUajiiPbbnr4RSXqMbppMZ4twUlUajiiPbbnr4RSXqMbLbmo03Rcq0K/cvhQ+3X:9HFHsGqCM6tNHFHsGqabmoMR18hQ+30k"
string(100) "48:9lUajiiPbbnr4RSXqMbLbmo03Rcq0K/cvhQ+3/M8M5BEaB1UlUajiiPbbnr4RSXX:9HFHsGqabmoMR18hQ+308sBdsHFHsGqy"
int(57)
int(75)
int(63)
