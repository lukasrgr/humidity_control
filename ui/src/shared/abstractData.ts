import { Directive } from "@angular/core";
import { ReceiveDataResponse, Service } from "./service";

@Directive()
export abstract class AbstractData {
    chartData: ReceiveDataResponse;
    constructor(
        public service: Service
    ) { }

    ngOnInit(): void {
        this.service.connectToWebsocket("receiveData").then((chartData) => {
            console.log("chartData", chartData)
            this.chartData = chartData as ReceiveDataResponse;
        }).finally(() => {
            this.createChart(this.chartData)
        })
    }

    protected abstract createChart(chartData: ReceiveDataResponse): void
}