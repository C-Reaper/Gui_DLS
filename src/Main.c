#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/DLS.h"

/*

OR 2 -> 1:
- NOT \ 
       AND - NOT
- NOT /


2 => f => 1:
f:= %0 = !(!$0 & !$1)

Functiontree:
n -> function(*ins,*outs)
t -> functionwrapper{ins,outs,functionwrapper}:

STD:
    AND(2,1),NOT(1,1)

FUNCS:
    AND,NOT,NOT,NOT

INPUTS:
    LIST: (Pins itself)
        VALUE,
        LIST: (FUNCS index,PIN index) (Pin IN to TARGET)

Counting how many inputs were already set:
    if ins set == ins there -> on execute STACK
    else                    -> on waiting STACK

*/


DLS dls;
GChip* focusedChip = NULL;
int focusedPin = -1;

void Setup(AlxWindow* w){
    ResizeAlxFont(16,16);
    dls = DLS_Make_Std(GetWidth(),GetHeight());
}
void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&dls.tv,w->Strokes,GetMouse());
    
    if(Stroke(ALX_KEY_ENTER).PRESSED){
        DLS_Execute(&dls);
    }

    if(Stroke(ALX_KEY_1).PRESSED){
        focusedChip = NULL;
        focusedPin = -1;
        DLS_AddChip(&dls,GetMouse(),"IN");
    }
    if(Stroke(ALX_KEY_2).PRESSED){
        focusedChip = NULL;
        focusedPin = -1;
        DLS_AddChip(&dls,GetMouse(),"OUT");
    }
    if(Stroke(ALX_KEY_3).PRESSED){
        focusedChip = NULL;
        focusedPin = -1;
        DLS_AddChip(&dls,GetMouse(),"AND");
    }
    if(Stroke(ALX_KEY_4).PRESSED){
        focusedChip = NULL;
        focusedPin = -1;
        DLS_AddChip(&dls,GetMouse(),"NOT");
    }

    if(Stroke(ALX_MOUSE_L).PRESSED){
        if(focusedPin>=0){
            Pin* fp = (Pin*)PVector_Get(&dls.pins,focusedPin);
            int itp = DLS_Pin_FindI(&dls,GetMouse());
            if(itp>=0){
                Pin* p = (Pin*)PVector_Get(&dls.pins,itp);
                if(fp->t==CIRCUIT_SIGNALTYPE_INPUT && p->t==CIRCUIT_SIGNALTYPE_OUTPUT)
                    Vector_Push(&dls.wires,(Wire[]){ Wire_New(focusedPin,itp) });
                if(fp->t==CIRCUIT_SIGNALTYPE_OUTPUT && p->t==CIRCUIT_SIGNALTYPE_INPUT)
                    Vector_Push(&dls.wires,(Wire[]){ Wire_New(itp,focusedPin) });
            }
            focusedPin = -1;
        }else{
            focusedChip = DLS_GChip_Find(&dls,GetMouse());
            focusedPin = DLS_Pin_FindI(&dls,GetMouse());
        }
    }
    if(Stroke(ALX_MOUSE_L).DOWN){
        if(focusedChip){
            const Vec2 wm = TransformedView_ScreenWorldPos(&dls.tv,GetMouse());
            focusedChip->p = wm;
        }
    }
    if(Stroke(ALX_KEY_REMOVE).PRESSED){
        if(focusedChip){
            const int iter = DLS_GChip_Iter(&dls,focusedChip);
            DLS_RemoveChip(&dls,iter);
        }
    }

    if(Stroke(ALX_MOUSE_R).PRESSED){
        GChip* fc = DLS_GChip_Find(&dls,GetMouse());
        if(fc){
            if(CStr_Cmp(fc->cw->name,"IN")){
                Pin* p = *(Pin**)Vector_Get(&fc->input,0);
                if(p->s == CIRCUIT_SIGNAL_HIGH) p->s = CIRCUIT_SIGNAL_LOW;
                else                            p->s = CIRCUIT_SIGNAL_HIGH;
            }
        }
    }
    if(Stroke(ALX_KEY_ENTER).PRESSED){
        DLS_Execute(&dls);
    }
    
    Clear(DARK_GRAY);

    DLS_Render(WINDOW_STD_ARGS,&dls);

    if(focusedPin>=0){
        Pin* p = (Pin*)PVector_Get(&dls.pins,focusedPin);
        const Vec2 pos = Vec2_Add(p->p,(Vec2){ PIN_SIZE*0.5f,PIN_SIZE*0.5f });
        const Vec2 sp = TransformedView_WorldScreenPos(&dls.tv,pos);
        RenderLine(sp,GetMouse(),RED,1.0f);
    }
}
void Delete(AlxWindow* w){
    focusedChip = NULL;
    focusedPin = -1;
    DLS_Free(&dls);
}

int main() {
    if(Create("Digital Logic Sim",1900,1000,1,1,Setup,Update,Delete)){
        Start();
    }
    return 0;
}
