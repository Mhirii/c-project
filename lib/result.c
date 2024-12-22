#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Result {
  int is_ok;
  union {
    void *ok;
    char *error;
  } value;
};

#define OK(x)                                                                  \
  (struct Result) {                                                            \
    .is_ok = 1, .value = {.ok = (void *)(x) }                                  \
  }
#define ERR(x)                                                                 \
  (struct Result) {                                                            \
    .is_ok = 0, .value = {.error = (x) }                                       \
  }

#define UNWRAP(result, type)                                                   \
  ({                                                                           \
    if (!result.is_ok) {                                                       \
      printf("Unwrap failed: %s\n", result.value.error);                       \
      exit(1);                                                                 \
    }                                                                          \
    (type) result.value.ok;                                                    \
  })

#define UNWRAP_OR(result, default_val, type)                                   \
  ({ result.is_ok ? (type)result.value.ok : default_val; })

struct Person {
  int age;
  char *name;
};

struct Result get_greeting(const char *name) {
  if (name == NULL) {
    return ERR("name is null");
  }
  char *greeting = malloc(strlen(name) + 8);
  if (greeting == NULL) {
    return ERR("memory allocation failed");
  }
  sprintf(greeting, "Hello %s!", name);
  return OK(greeting);
}

struct Result create_person(int age, const char *name) {
  struct Result *res = malloc(sizeof(struct Result));

  if (age < 0) {
    res->is_ok = 0;
    return ERR("age cannot be negative");
  }
  if (name == NULL) {
    return ERR("name cannot be null");
  }

  struct Person *person = malloc(sizeof(struct Person));
  if (person == NULL) {
    return ERR("memory allocation failed");
  }

  person->age = age;
  person->name = strdup(name);
  if (person->name == NULL) {
    free(person);
    return ERR("name allocation failed");
  }

  return OK(person);
}
