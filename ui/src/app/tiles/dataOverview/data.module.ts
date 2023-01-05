import { CommonModule } from '@angular/common';
import { RelayComponent } from './../dataOverview/relay/relay';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { DataOverviewTile } from './dataOverview';
import { TemperatureComponent } from './temperature/temperature';
import { HumidityComponent } from './humidity/humidity';

@NgModule({
    imports: [
        CommonModule
    ],
    declarations: [
        RelayComponent,
        TemperatureComponent,
        HumidityComponent,
        DataOverviewTile,
    ],
    exports: [
        DataOverviewTile,
        RelayComponent,
        HumidityComponent,
        TemperatureComponent,
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class DataOverviewModule { }