import { CommonModule } from '@angular/common';
import { RelayComponent } from './../dataOverview/relay/relay';
import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from "@angular/core";
import { DataOverviewTile } from './dataOverview';
import { TemperatureComponent } from './temperature/temperature';
import { HumidityComponent } from './humidity/humidity';
import { LastReadTimeComponent } from './lastReadTime/lastReadTime';

@NgModule({
    imports: [
        CommonModule
    ],
    declarations: [
        RelayComponent,
        TemperatureComponent,
        HumidityComponent,
        DataOverviewTile,
        LastReadTimeComponent
    ],
    exports: [
        DataOverviewTile,
        RelayComponent,
        HumidityComponent,
        TemperatureComponent,
        LastReadTimeComponent
    ],
    schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class DataOverviewModule { }