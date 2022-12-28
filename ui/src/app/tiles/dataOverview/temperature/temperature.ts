import { Component } from "@angular/core";
import { Service } from "src/shared/service";

@Component({
    selector: "temperatureComponent",
    templateUrl: "./temperature.html"
})
export class TemperatureComponent {

    public temperature: number;
    constructor(
        private service: Service
    ) { }
    ngOnInit() {
        this.service.latestData.subscribe(data => {
            this.temperature = data.temperature
        })
    }
}

export type GetCurrentTemperatureResponse = {
    temperature: number[],
    timestamps: string[]
}