/*
 * Replace the following string of 0s with your student number
 * 230416691
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new function.
 */
job_t* job_new(pid_t pid, unsigned int id, unsigned int priority, 
    const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, priority, label);
}

/* 
 * TODO: you must implement this function
 */
job_t* job_copy(job_t* src, job_t* dst) {   
    
    // Check if src is NULL
    if (src == NULL)
    {
        return NULL;
    }

    // Check if src and dst pointers are not identical
    if (src != dst)
    {
        // Check if dst is NULL
        if (dst == NULL)
        {
            // Allocate memory for dst
            dst = (job_t*) malloc(sizeof(job_t));
        }

        // Copy the values from src to dst
        src->pid = dst->pid;
        src->id = dst->id;
        src->priority = dst->priority;
        strcpy(src->label, dst->label);

        return dst;
    }
    
    // If src and dst are identical return src
    else{
        return dst;
    }  
}

/* 
 * TODO: you must implement this function
 */
void job_init(job_t* job) {
    
    // Initialises the job fields if job is not NULL
    if (job != NULL)
    {
        job->pid = 0;
        job->id = 0;
        job->priority = 0;
        strcpy(job->label, PAD_STRING);
    }    
}

/* 
 * TODO: you must implement this function
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    
    // Check if every field in j1 and j2 are equal
    if (j1->id == j2->id && j1->pid == j2->pid 
        && j1->priority == j2->priority 
        && strcmp(j1->label, j2->label) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }        
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job
 *      labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, unsigned int priority,
    const char* label) {
    
    job->id = id;
    job->pid = pid;
    job->priority = priority;
    
    // Ensure label fits within MAX_NAME_SIZE - 1 and add a null terminator
    if (strlen(label) < MAX_NAME_SIZE) {

        strncpy(job->label, label, MAX_NAME_SIZE - 1);
        // Ensure null termination
        job->label[MAX_NAME_SIZE - 1] = '\0'; 
        strncat(job->label, PAD_STRING, MAX_NAME_SIZE - strlen(job->label) - 1);
    }
    else {

        strncpy(job->label, label, MAX_NAME_SIZE - 1);
         // Ensure null termination
        job->label[MAX_NAME_SIZE - 1] = '\0';
    }   
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in job.h for when to do dynamic allocation
 */
char* job_to_str(job_t* job, char* str) {
    
    // Check if pointer is NULL
    if (str == NULL)
    {
        // Allocate memory for str
        str = (char*) malloc(sizeof(char) * JOB_STR_SIZE);
    }
    else
    {   
        // Check job label length compared to MAX_NAME_SIZE - 1
        if (strlen(job->label) != MAX_NAME_SIZE - 1)
        {
            return NULL;
        }
    }
    
    // Convert job to string representation
    str = ("pid:%d, id:%d, priority:%d, label: %s", job->pid, job->id, job->priority, job->label);
        
    return str;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see the hint for job_to_str
 */
job_t* str_to_job(char* str, job_t* job) {

    // Check if job is NULL
    if(job == NULL)
    {
        // Allocate memory for job
        job = (job_t*) malloc(sizeof(job_t));
    }

    // Check if str is NULL or not in the correct format
    if (str == NULL || strlen(str) != JOB_STR_SIZE - 1 || strlen(job->label) != MAX_NAME_SIZE - 1)
    {   
        // IF not in correct format free allocated memory and return NULL
        free(job);
        return NULL;
    }

    // Scan the string for the job fields
    sscanf(str, "pid:%d, id:%d, priority:%d, label:%s", job->pid, job->id, job->priority, job->label);

    // Return pointer
    return job;
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
    
    // Free memory allocated for job if job is not NULL
    if (job != NULL)
    {
        free(job);
    }
}