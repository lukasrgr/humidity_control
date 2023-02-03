import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { DatePickerComponent } from "./datepicker/datepicker.component";
import { MatSnackBarModule } from "@angular/material/snack-bar";
import { MatFormFieldModule } from "@angular/material/form-field";
import { MatButtonModule } from "@angular/material/button";
import { MatInputModule } from "@angular/material/input";
import { MatDatepickerModule } from "@angular/material/datepicker";
import { MatNativeDateModule } from "@angular/material/core";
import { ReactiveFormsModule } from "@angular/forms";



@NgModule({
    declarations: [
        DatePickerComponent
    ],
    imports: [

        // Angular Material
        MatSnackBarModule,
        MatFormFieldModule,
        MatButtonModule,
        MatInputModule,
        MatDatepickerModule,
        MatNativeDateModule,
        ReactiveFormsModule
    ],
    schemas: [
        CUSTOM_ELEMENTS_SCHEMA
    ],
    exports: [
        MatSnackBarModule,
        MatFormFieldModule,
        MatButtonModule,
        MatInputModule,
        MatDatepickerModule,
        MatNativeDateModule,
        DatePickerComponent,
    ]
})
export class SharedModule { }
