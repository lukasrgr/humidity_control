import { SharedModule } from 'src/shared/shared.module';
import { MatDatepickerModule } from '@angular/material/datepicker';
import { CommonModule } from '@angular/common';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { ChartComponent } from "./chart";

@NgModule({
    declarations: [
        ChartComponent
    ],
    exports: [
        ChartComponent
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA],
    imports: [
        CommonModule,
        MatDatepickerModule,
        SharedModule,
    ]
})
export class Chart { }