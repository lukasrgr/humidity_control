import { ConsumptionCalculationTile } from './consumptionCalculation/consumptionCalculation';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { DataOverviewTile } from "./dataOverview/dataOverview";
import { DataOverviewModule } from './dataOverview/data.module';

@NgModule({
    imports: [
        DataOverviewModule
    ],
    declarations: [
        ConsumptionCalculationTile
    ],
    exports: [
        ConsumptionCalculationTile,
        DataOverviewModule
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class Tiles { }