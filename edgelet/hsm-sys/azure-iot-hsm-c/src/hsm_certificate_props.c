// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "azure_c_shared_utility/xlogging.h"

#include "hsm_certificate_props.h"

typedef struct HSM_CERT_PROPS_TAG
{
    CERTIFICATE_TYPE type;
    char *alias;
    char *issuer_alias;
    char *common_name;
    char *state_name;
    char *locality;
    char *org_name;
    char *org_unit;
    char country_name[3];
    uint64_t validity;
} HSM_CERT_PROPS;

CERT_PROPS_HANDLE cert_properties_create(void)
{
    HSM_CERT_PROPS *result;

    if ((result = (HSM_CERT_PROPS *)malloc(sizeof(HSM_CERT_PROPS))) == NULL)
    {
        LogError("Failure allocating HSM_CERT_PROPS");
    }
    else
    {
        memset(result, 0, sizeof(HSM_CERT_PROPS));
    }
    return result;
}

void cert_properties_destroy(CERT_PROPS_HANDLE handle)
{
    if (handle != NULL)
    {
        free(handle->alias);
        free(handle->issuer_alias);
        free(handle->common_name);
        free(handle->state_name);
        free(handle->locality);
        free(handle->org_name);
        free(handle->org_unit);
        free(handle);
    }
}

int set_validity_seconds(CERT_PROPS_HANDLE handle, uint64_t validity_mins)
{
    int result;
    if (handle == NULL || validity_mins == 0)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        handle->validity = validity_mins;
        result = 0;
    }
    return result;
}

uint64_t get_validity_seconds(CERT_PROPS_HANDLE handle)
{
    uint64_t result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = 0;
    }
    else
    {
        result = handle->validity;
    }
    return result;
}

int set_common_name(CERT_PROPS_HANDLE handle, const char *common_name)
{
    int result;
    if (handle == NULL || common_name == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->common_name != NULL)
        {
            free(handle->common_name);
            handle->common_name = NULL;
        }

        size_t len = strlen(common_name);
        if (len == 0)
        {
            LogError("common_name is zero length");
            result = __LINE__;
        }
        else
        {
            handle->common_name = (char *)malloc(len + 1);
            if (handle->common_name == NULL)
            {
                LogError("Failure allocating common_name");
                result = __LINE__;
            }
            else
            {
                memset(handle->common_name, 0, len + 1);
                memcpy(handle->common_name, common_name, len);
                result = 0;
            }
        }
    }
    return result;
}

const char *get_common_name(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->common_name;
    }
    return result;
}

int set_country_name(CERT_PROPS_HANDLE handle, const char *country_name)
{
    int result;
    if (handle == NULL || country_name == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else if (strlen(country_name) > 2)
    {
        LogError("Invalid country name length specified");
        result = __LINE__;
    }
    else
    {
        strcpy(handle->country_name, country_name);
        result = 0;
    }
    return result;
}

const char *get_country_name(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        if (strlen(handle->country_name) > 0)
        {
            result = handle->country_name;
        }
        else
        {
            result = NULL;
        }
    }
    return result;
}

int set_state_name(CERT_PROPS_HANDLE handle, const char *state_name)
{
    int result;
    if (handle == NULL || state_name == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->state_name != NULL)
        {
            free(handle->state_name);
        }

        size_t len = strlen(state_name);
        handle->state_name = (char *)malloc(len + 1);
        if (handle->state_name == NULL)
        {
            LogError("Failure allocating state_name");
            result = __LINE__;
        }
        else
        {
            memset(handle->state_name, 0, len + 1);
            memcpy(handle->state_name, state_name, len);
            result = 0;
        }
    }
    return result;
}

const char *get_state_name(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->state_name;
    }
    return result;
}

int set_locality(CERT_PROPS_HANDLE handle, const char *locality)
{
    int result;
    if (handle == NULL || locality == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->locality != NULL)
        {
            free(handle->locality);
        }

        size_t len = strlen(locality);
        handle->locality = (char *)malloc(len + 1);
        if (handle->locality == NULL)
        {
            LogError("Failure allocating locality");
            result = __LINE__;
        }
        else
        {
            memset(handle->locality, 0, len + 1);
            memcpy(handle->locality, locality, len);
            result = 0;
        }
    }
    return result;
}

const char *get_locality(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->locality;
    }
    return result;
}

int set_organization_name(CERT_PROPS_HANDLE handle, const char *org_name)
{
    int result;
    if (handle == NULL || org_name == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->org_name != NULL)
        {
            free(handle->org_name);
        }

        size_t len = strlen(org_name);
        handle->org_name = (char *)malloc(len + 1);
        if (handle->org_name == NULL)
        {
            LogError("Failure allocating common_name");
            result = __LINE__;
        }
        else
        {
            memset(handle->org_name, 0, len + 1);
            memcpy(handle->org_name, org_name, len);
            result = 0;
        }
    }
    return result;
}

const char *get_organization_name(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->org_name;
    }
    return result;
}

int set_organization_unit(CERT_PROPS_HANDLE handle, const char *ou)
{
    int result;
    if (handle == NULL || ou == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->org_unit != NULL)
        {
            free(handle->org_unit);
        }

        size_t len = strlen(ou);
        handle->org_unit = (char *)malloc(len + 1);
        if (handle->org_unit == NULL)
        {
            LogError("Failure allocating ou");
            result = __LINE__;
        }
        else
        {
            memset(handle->org_unit, 0, len + 1);
            memcpy(handle->org_unit, ou, len);
            result = 0;
        }
    }
    return result;
}

const char *get_organization_unit(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->org_unit;
    }
    return result;
}

int set_certificate_type(CERT_PROPS_HANDLE handle, CERTIFICATE_TYPE type)
{
    int result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else if ((type != CERTIFICATE_TYPE_CLIENT) &&
             (type != CERTIFICATE_TYPE_SERVER) &&
             (type != CERTIFICATE_TYPE_CA))
    {
        LogError("Error invalid certificate type", type);
        result = __LINE__;
    }
    else
    {
        handle->type = type;
        result = 0;
    }
    return result;
}

CERTIFICATE_TYPE get_certificate_type(CERT_PROPS_HANDLE handle)
{
    CERTIFICATE_TYPE result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = CERTIFICATE_TYPE_UNKNOWN;
    }
    else
    {
        result = handle->type;
    }
    return result;
}

int set_issuer_alias(CERT_PROPS_HANDLE handle, const char *issuer_alias)
{
    int result;
    if (handle == NULL || issuer_alias == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->issuer_alias != NULL)
        {
            free(handle->issuer_alias);
            handle->issuer_alias = NULL;
        }

        size_t len = strlen(issuer_alias);
        if (len == 0)
        {
            LogError("Issuer alias is zero length");
            result = __LINE__;
        }
        else
        {
            handle->issuer_alias = (char *)malloc(len + 1);
            if (handle->issuer_alias == NULL)
            {
                LogError("Failure allocating issuer_alias");
                result = __LINE__;
            }
            else
            {
                memset(handle->issuer_alias, 0, len + 1);
                memcpy(handle->issuer_alias, issuer_alias, len);
                result = 0;
            }
        }
    }
    return result;
}

const char *get_issuer_alias(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->issuer_alias;
    }
    return result;
}

int set_alias(CERT_PROPS_HANDLE handle, const char *alias)
{
    int result;
    if (handle == NULL || alias == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = __LINE__;
    }
    else
    {
        if (handle->alias != NULL)
        {
            free(handle->alias);
        }

        size_t len = strlen(alias);
        if (len == 0)
        {
            LogError("Alias is zero length");
            result = __LINE__;
        }
        else
        {
            handle->alias = (char *)malloc(len + 1);
            if (handle->alias == NULL)
            {
                LogError("Failure allocating alias");
                result = __LINE__;
            }
            else
            {
                memset(handle->alias, 0, len + 1);
                memcpy(handle->alias, alias, len);
                result = 0;
            }
        }
    }
    return result;
}

const char *get_alias(CERT_PROPS_HANDLE handle)
{
    const char *result;
    if (handle == NULL)
    {
        LogError("Invalid parameter encounterered");
        result = NULL;
    }
    else
    {
        result = handle->alias;
    }
    return result;
}