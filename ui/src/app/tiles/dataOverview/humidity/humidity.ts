import { Service } from 'src/shared/service';
import { Component } from "@angular/core";

@Component({
    selector: "humidityComponent",
    templateUrl: "./humidity.html"
})
export class HumidityComponent {
    public humidity: number;

    constructor(
        private service: Service
    ) { }

    ngOnInit() {
        this.service.latestData.subscribe(data => {
            this.humidity = data.humidity
        })
    }
}

export enum RelayState {
    RELAY_CLOSED,
    RELAY_OPEN
}

export type GetCurrentRelayStateResponse = {
    relay: number[],
    timestamps: string[]
}