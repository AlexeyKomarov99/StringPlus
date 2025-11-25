#include <check.h>
#include <stdio.h>
#include <stdlib.h>

TCase *tcase_memchr(void);
TCase *tcase_memcmp(void);
TCase *tcase_memcpy(void);
TCase *tcase_memset(void);
TCase *tcase_strncat(void);
TCase *tcase_strchr(void);
TCase *tcase_strncmp(void);
TCase *tcase_strncpy(void);
TCase *tcase_strcspn(void);
TCase *tcase_strlen(void);
TCase *tcase_strpbrk(void);
TCase *tcase_strrchr(void);
TCase *tcase_strstr(void);
TCase *tcase_strtok(void);
TCase *tcase_strerror(void);
TCase *tcase_to_upper(void);
TCase *tcase_to_lower(void);
TCase *tcase_insert(void);
TCase *tcase_trim(void);
TCase *tcase_sprintf(void);
TCase *tcase_sscanf(void);

Suite *string_suite(void) {
  Suite *s = suite_create("String Library Tests");

  suite_add_tcase(s, tcase_memchr());
  suite_add_tcase(s, tcase_memcmp());
  suite_add_tcase(s, tcase_memcpy());
  suite_add_tcase(s, tcase_memset());
  suite_add_tcase(s, tcase_strncat());
  suite_add_tcase(s, tcase_strchr());
  suite_add_tcase(s, tcase_strncmp());
  suite_add_tcase(s, tcase_strncpy());
  suite_add_tcase(s, tcase_strcspn());
  suite_add_tcase(s, tcase_strlen());
  suite_add_tcase(s, tcase_strpbrk());
  suite_add_tcase(s, tcase_strrchr());
  suite_add_tcase(s, tcase_strstr());
  suite_add_tcase(s, tcase_strtok());
  suite_add_tcase(s, tcase_strerror());
  suite_add_tcase(s, tcase_to_upper());
  suite_add_tcase(s, tcase_to_lower());
  suite_add_tcase(s, tcase_insert());
  suite_add_tcase(s, tcase_trim());
  suite_add_tcase(s, tcase_sprintf());
  suite_add_tcase(s, tcase_sscanf());

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}