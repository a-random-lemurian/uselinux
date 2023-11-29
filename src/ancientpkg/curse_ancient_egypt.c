/* AE = [A]ncient [E]gypt */
#ifndef OMIT_ANCIENT_EGYPT_CURSE

#include "ancientpkg.h"
#include <assert.h>
#include <common/utils.h>
#include "curse.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

static int last_decode_attempt_was_error = 0;
static int consecutive_decode_failures = 0;
static int first_failed_hglyph = 0;

int deal_with_single_hglyph_error(int i, int rc)
{

    char endch = '\n';

    printf("[Decode] "BHRED"Error:"reset" Failed to decode hieroglyph %d.",
           i);

    if (last_decode_attempt_was_error == 2)
    {
        first_failed_hglyph = i;
        last_decode_attempt_was_error = 1;
    }

    if (last_decode_attempt_was_error == 1)
    {
        consecutive_decode_failures++;
        printf(" (%d consecutive failures)", consecutive_decode_failures);
    }
    else
    {
        last_decode_attempt_was_error = 2;
    }

    printf("%c", endch);
    fflush(stdout);

    return 0;
}

int decode_single_hglyph(DigControlFlags* dcf, DigStatistics* dst)
{
    if (!dcf->dry_run)
    {
        msleep(randint(40, 400));
    }


    int n = randint(1, 120);

    if (n > 115)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int remove_error_state()
{
    last_decode_attempt_was_error = 0;
    consecutive_decode_failures = 0;

    return 0;
}

int decode_hieroglyphs(DigControlFlags* dcf, DigStatistics* dst)
{
    int i = 0;
    int rc = 0;
    int hglyphs_required = randint(4, 90);
    int hglyphs_decoded = 0;

    while (hglyphs_decoded < hglyphs_required)
    {
        rc = decode_single_hglyph(dcf, dst);

        if (rc != 0)
        {
            deal_with_single_hglyph_error(i, rc);
        }
        else if (rc == 0)
        {
            remove_error_state();

            printf("[Decode] Decoded hieroglyph %d.\n", i);
            hglyphs_decoded++;
        }

        i++;
    }

    printf("[Decon] Was able to derive curse mitigation method from "
           "hieroglpyhs.\n");
    printf("[Decon] Broke curse.\n");
}

int cmit_ancient_egypt_curse(int n, DigControlFlags *dcf, DigStatistics *dst)
{
    if (strncasecmp(dcf->location, "Egypt", 6) != 0)
    {
        return 0;
    }

    int curse_class = randint(1, 10);

    assert(curse_class > 0);
    assert(curse_class <= 10);

    printf(WARN "Current package contains an ancient Egyptian curse of "
                "class %d.\n",
           curse_class);

    int j = randint(40, 100);
    int k = j * curse_class;

    for (int i = 0; i < k; i++)
    {
        printf("[Decon] Removing curse from package (step %d of %d).\n", i, k);

        int l = randint(1, 900);

        if (l > 850)
        {
            printf("[Decon] Warning: Package fragment contains sub-curse.\n");
            decode_hieroglyphs(dcf, dst);
        }
    }

    return 0;
}

#endif