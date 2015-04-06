/**
 *
 * php_ssdeep
 *
 * http://treffynnon.github.com/php_ssdeep/
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

#ifndef PHP_SSDEEP_H
#   define PHP_SSDEEP_H 1
#   define PHP_SSDEEP_VERSION "1.0.4"
#   define PHP_SSDEEP_EXTNAME "ssdeep"
    PHP_FUNCTION(ssdeep_fuzzy_hash);
    PHP_FUNCTION(ssdeep_fuzzy_compare);
    PHP_FUNCTION(ssdeep_fuzzy_hash_filename);

    extern zend_module_entry php_ssdeep_module_entry;
#   define phpext_php_ssdeep_ptr &php_ssdeep_module_entry
#endif
