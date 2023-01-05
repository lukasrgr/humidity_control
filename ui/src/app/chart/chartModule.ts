import { CommonModule } from '@angular/common';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { ChartComponent } from "./chart";

@NgModule({
    imports: [
        CommonModule
    ],
    declarations: [
        ChartComponent
    ],
    exports: [
        ChartComponent
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class Chart { }