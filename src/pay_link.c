#include "modding.h"
#include "global.h"
#include "recomputils.h"

RECOMP_HOOK("Player_Update") void onPlayer_Update(Player* this, PlayState* play) {
    if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_L)) {
        Rupees_ChangeBy(0);
        recomp_printf("button pressed\n");
    }
}

RECOMP_HOOK_RETURN("Rupees_ChangeBy")
void afterRupees_ChangeBy() {
    recomp_printf("rupee accumulator: %d\n", gSaveContext.rupeeAccumulator);
    if (gSaveContext.rupeeAccumulator > 0 && ((gSaveContext.save.saveInfo.playerData.rupees + gSaveContext.rupeeAccumulator) > CUR_CAPACITY(UPG_WALLET))) {
    recomp_printf("overflow\n");
    u32 overflow = (gSaveContext.save.saveInfo.playerData.rupees + gSaveContext.rupeeAccumulator) - CUR_CAPACITY(UPG_WALLET);
    gSaveContext.rupeeAccumulator -= overflow;
    recomp_printf("remainder %d\n", overflow);
    HS_SET_BANK_RUPEES(HS_GET_BANK_RUPEES() + overflow);
    recomp_printf("bank amount %d\n", HIGH_SCORE(HS_BANK_RUPEES));
    }
}