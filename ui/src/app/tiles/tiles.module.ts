import { ConsumptionCalculationTile } from './consumptionCalculation/consumptionCalculation';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { DataOverviewTile } from "./dataOverview/dataOverview";

@NgModule({
    declarations: [
        DataOverviewTile,
        ConsumptionCalculationTile
    ],
    exports: [
        DataOverviewTile,
        ConsumptionCalculationTile
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class Tiles { }