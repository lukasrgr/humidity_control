import { Service } from './../shared/service';
import { Tiles } from './tiles/tiles.module';
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { IonicModule } from '@ionic/angular';
import { Chart } from './chart/chartModule';
import { NgChartsModule } from 'ng2-charts';
import { CommonModule } from '@angular/common';


@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    CommonModule,
    Chart,
    Tiles,
    NgChartsModule,
    BrowserModule,
    AppRoutingModule,
    IonicModule.forRoot(),
  ],
  providers: [
    Service,
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
