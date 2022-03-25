#include <curl/curl.h>
#include "json.h/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
    char path[100];
    char output[200];
    FILE *fp; int status;

    char *req = "curl -s 'http://router.project-osrm.org/route/v1/driving/%lf,%lf;%lf,%lf;%lf,%lf;%lf,%lf?overview=false'";
    snprintf(output, 200, req, 76.9155196, 43.3164987, 76.79973595, 43.23044825, 76.8967166, 43.2329546, 76.9155196, 43.3164987);
    //printf("%s\n", output);
    fp = popen(output, "r");
    if(fp == NULL) {
        return -2.0;
    }
    char *json = (char*)malloc(1000 * sizeof(char));
    fscanf(fp, "%s", json);
    //printf("%s\n", json);

    //const char json[] = "{\"a\" : true, \"b\" : [false, null, \"foo\"]}";
    struct json_value_s* root = json_parse(json, strlen(json));
    assert(root->type == json_type_object);

    struct json_object_s* object = (struct json_object_s*)root->payload;

    //printf("%lu\n", object->length);
    struct json_object_element_s* code = object->start;
    assert(0 == strcmp(((struct json_string_s*)code->value->payload)->string, "Ok"));

    struct json_object_element_s* waypoints = code->next;
    struct json_object_element_s* routes = waypoints->next;
    struct json_object_element_s* legs = ((struct json_object_s*)(((((struct json_array_s*)routes->value->payload)->start))->value->payload))->start;
    struct json_array_s* steps = (struct json_array_s*)legs->value->payload;

    char *eptr;
    struct json_array_element_s* stepu = steps->start;
    double distance1 = strtod(((struct json_number_s*)(((struct json_object_element_s*)(((struct json_object_s*)stepu->value->payload)->start->next->next))->value->payload))->number, &eptr);
    stepu = stepu->next;
    double distance2 = strtod(((struct json_number_s*)(((struct json_object_element_s*)(((struct json_object_s*)stepu->value->payload)->start->next->next))->value->payload))->number, &eptr);
    stepu = stepu->next;
    double distance3 = strtod(((struct json_number_s*)(((struct json_object_element_s*)(((struct json_object_s*)stepu->value->payload)->start->next->next))->value->payload))->number, &eptr);
    printf("%lf %lf %lf\n", distance1, distance2, distance3);




    //struct json_object_s* legs = ((struct json_object_s*)(((struct json_array_s*)routes->value->payload)->start))->start->name->string;
    //printf("Now: %s\n", );//->value->type;
    //assert(code->);
    //assert(object->length == 2);

    //struct json_object_element_s* a = object->start;
    //printf("%s %lu\n", a->name->string, a->value->type);

    /*
    Вот все типы, которые есть:
    Цифра 4 говорит, что это значение формата true
    enum json_type_e {
      json_type_string,
      json_type_number,
      json_type_object,
      json_type_array,
      json_type_true,
      json_type_false,
      json_type_null
    };
    */


    /*
    struct json_string_s* a_name = a->name;

    assert(0 == strcmp(a_name->string, "a"));
    assert(a_name->string_size == strlen("a"));

    struct json_value_s* a_value = a->value;
    assert(a_value->type == json_type_true);
    assert(a_value->payload == NULL);

    struct json_object_element_s* b = a->next;
    assert(b->next == NULL);

    struct json_string_s* b_name = b->name;
    assert(0 == strcmp(b_name->string, "b"));
    assert(b_name->string_size == strlen("b"));

    struct json_value_s* b_value = b->value;
    assert(b_value->type == json_type_array);

    struct json_array_s* array = (struct json_array_s*)b_value->payload;
    assert(array->length == 3);

    struct json_array_element_s* b_1st = array->start;

    struct json_value_s* b_1st_value = b_1st->value;
    assert(b_1st_value->type == json_type_false);
    assert(b_1st_value->payload == NULL);

    struct json_array_element_s* b_2nd = b_1st->next;

    struct json_value_s* b_2nd_value = b_2nd->value;
    assert(b_2nd_value->type == json_type_null);
    assert(b_2nd_value->payload == NULL);

    struct json_array_element_s* b_3rd = b_2nd->next;
    assert(b_3rd->next == NULL);

    struct json_value_s* b_3rd_value = b_3rd->value;
    assert(b_3rd_value->type == json_type_string);

    struct json_string_s* string = (struct json_string_s*)b_3rd_value->payload;
    assert(0 == strcmp(string->string, "foo"));
    assert(string->string_size == strlen("foo"));
    */
    /* Don't forget to free the one allocation! */
    free(root);
    return 0;
}