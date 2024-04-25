#include <tcl.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Tcl_FindExecutable(argv[0]);
    Tcl_Interp *interp = Tcl_CreateInterp();
    if (interp == NULL) {
        fprintf(stderr, "fail to create tcl interpreter\n");
        return EXIT_FAILURE;
    }

    int rv = 0;
    if (argc > 1) {
        rv = Tcl_ExprString(interp, argv[1]);
    } else {
        rv = Tcl_Eval(interp, "puts \"hello world\"");
    }

    if (rv != TCL_OK) {
        fprintf(stderr, "fail to evaluate script\n");
        Tcl_DeleteInterp(interp);
        return EXIT_FAILURE;
    }

    const char *result = Tcl_GetStringResult(interp);
    printf("%s", result);
    Tcl_DeleteInterp(interp);
    return EXIT_SUCCESS;
}
