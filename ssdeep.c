/**
 *
 * php_ssdeep
 *
 * http://treffynnon.github.com/php_ssdeep/
 *
 * A PHP extension to expose ssdeep functionality for fuzzy
 * hashing and comparing.
 *
 * Version 1.2.0
 *
 * BSD Licensed.
 *
 * Copyright (c) 2018, Simon Holywell
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "SAPI.h"
#include "php_ssdeep.h"
#include <fuzzy.h>

/* True global resources - no need for thread safety here */
ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_hash, 0, 0, 1)
    ZEND_ARG_INFO(0, to_hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_hash_filename, 0, 0, 1)
    ZEND_ARG_INFO(0, file_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_compare, 0, 0, 2)
    ZEND_ARG_INFO(0, signature1)
    ZEND_ARG_INFO(0, signature2)
ZEND_END_ARG_INFO()

/* {{{ ssdeep_functions[]
 */
const zend_function_entry ssdeep_functions[] = {
    PHP_FE(ssdeep_fuzzy_hash, arginfo_ssdeep_fuzzy_hash)
    PHP_FE(ssdeep_fuzzy_hash_filename, arginfo_ssdeep_fuzzy_hash_filename)
    PHP_FE(ssdeep_fuzzy_compare, arginfo_ssdeep_fuzzy_compare)
#ifdef PHP_FE_END
    PHP_FE_END
#else
    { NULL, NULL, NULL } /* Must be the last line in ssdeep_functions[] */
#endif
};
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ssdeep) {
    php_info_print_table_start();
    php_info_print_table_row(2, PHP_SSDEEP_EXTNAME " Module", "enabled");
    php_info_print_table_row(2, "version", PHP_SSDEEP_VERSION);
    if (sapi_module.phpinfo_as_text) {
        /* No HTML for you */
        php_info_print_table_row(2, "By",
                "Simon Holywell\nhttp://www.simonholywell.com");
    } else {
        /* HTMLified version */
        php_printf("<tr>"
                "<td class=\"v\">By</td>"
                "<td class=\"v\">"
                "<a href=\"http://www.simonholywell.com\""
                " alt=\"Simon Holywell\">"
                "Simon Holywell"
                "</a></td></tr>");
    }
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto string ssdeep_fuzzy_hash(string to_hash)
 */
PHP_FUNCTION(ssdeep_fuzzy_hash) {
    char hash [FUZZY_MAX_RESULT];
    char *to_hash;
    size_t to_hash_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(to_hash, to_hash_len)
    ZEND_PARSE_PARAMETERS_END();

    if (0 != fuzzy_hash_buf((unsigned char *) to_hash, (uint32_t)to_hash_len, (char*)&hash)) {
        RETURN_FALSE;
    } else {
        RETURN_STRING((char*)&hash);
    }
}
/* }}} */

/* {{{ proto string ssdeep_fuzzy_hash_filename(string file_name)
 */
PHP_FUNCTION(ssdeep_fuzzy_hash_filename) {
    char *file_name;
    size_t file_name_len;
    char hash [FUZZY_MAX_RESULT];

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(file_name, file_name_len)
    ZEND_PARSE_PARAMETERS_END();

    if (0 != fuzzy_hash_filename(file_name, (char*)&hash)) {
        RETURN_FALSE;
    } else {
        RETURN_STRING((char*)&hash);
    }
}
/* }}} */

/* {{{ proto long ssdeep_fuzzy_compare(string signature1, string signature2)
 */
PHP_FUNCTION(ssdeep_fuzzy_compare) {
    char *signature1 = NULL;
    size_t signature1_len;
    char *signature2 = NULL;
    size_t signature2_len;
    int match;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(signature1, signature1_len)
        Z_PARAM_STRING(signature2, signature2_len)
    ZEND_PARSE_PARAMETERS_END();

    match = fuzzy_compare(signature1, signature2);

	if (UNEXPECTED(match < 0 || match > 100)) {
	    RETURN_FALSE;
	} else {
        RETURN_LONG(match);
	}
}
/* }}} */

/* {{{ ssdeep_module_entry
 */
zend_module_entry ssdeep_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_SSDEEP_EXTNAME,
    ssdeep_functions,
    NULL /* PHP_MINIT(ssdeep) */,
    NULL /* PHP_MSHUTDOWN(ssdeep) */,
    NULL /* PHP_RINIT(ssdeep) */, /* Replace with NULL if there's nothing to do at request start */
    NULL /* PHP_RSHUTDOWN(ssdeep)*/, /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(ssdeep),
    PHP_SSDEEP_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SSDEEP
ZEND_GET_MODULE(ssdeep)
#endif
